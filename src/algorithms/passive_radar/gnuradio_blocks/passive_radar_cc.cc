/* -*- c++ -*- */
/* 
 * Copyright 2018 Dennis Chuprakov
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "passive_radar_cc.h"
#include "GPS_L1_CA.h"
#include <pmt/pmt.h>
#include <gnuradio/tags.h>
#include <volk/volk.h>
#include <volk_gnsssdr/volk_gnsssdr.h>
#include <gnuradio/filter/firdes.h>
#include <thread>
#include <limits> 
#include <algorithm> 
#include <fstream>
#include <iostream>
#include <sstream>

const float DOPPLER_DEFINITION = 0.25;
const float MAX_TIME_SHIFT     = 0.1;
const float eps = std::numeric_limits<float>::epsilon();
const double GAIN = 1.0;
const double END_PASS_BAND = 0.44;
const double START_STOP_BAND = 0.49;
const double ATTENUATION = 20;
const float DOPPLER_RANGE = 5000;
gr::filter::firdes::win_type WINDOW = gr::filter::firdes::WIN_HAMMING;
unsigned int FILTER_SIZE = 32;

passive_radar_cc_sptr make_passive_radar_cc( 
					    float fs_in,
					    float duration,
					    unsigned int sources_count,
					    unsigned int channels_count,
					    unsigned int vector_length,
					    std::vector<unsigned int> IDs
					     )
{
  return passive_radar_cc_sptr (new passive_radar_cc(
						     fs_in,
						     duration,
						     sources_count,
						     channels_count,
						     vector_length,
						     IDs
						     ));
}

/*
 * The private constructor
 */
passive_radar_cc::passive_radar_cc(
				   float fs_in,
				   float duration,
				   unsigned int sources_count,
				   unsigned int channels_count ,
				   unsigned int vector_length,
				   std::vector<unsigned int> IDs
				   )
  : gr::sync_block::sync_block("passive_radar",
			       gr::io_signature::make(1, -1, sizeof(gr_complex)),
			       gr::io_signature::make(0, 0, 0)),
    d_conditioners_count(sources_count),
    d_fs_in(fs_in),
    d_channels_count(channels_count)
{

  d_conv_chunk = pow(2, ceil(log2(static_cast<unsigned int> (duration * fs_in))));
  d_duration = d_conv_chunk/d_fs_in;
  
  d_IDs = IDs;
  d_run_detector = false;
  float doppler_step = (1/d_duration)*DOPPLER_DEFINITION;
  d_resampling_step = static_cast<unsigned int>(MAX_TIME_SHIFT/(GPS_L1_CA_CODE_RATE_HZ*d_duration) *GPS_L1_FREQ_HZ/doppler_step);
            
  std::vector<float> taps = gr::filter::firdes::low_pass_2(
							   GAIN,
							   fs_in*FILTER_SIZE,
							   fs_in*END_PASS_BAND,
							   fs_in*(START_STOP_BAND-END_PASS_BAND),
							   ATTENUATION,
							   WINDOW
							   );
      
  d_resamp = new gr::filter::kernel::pfb_arb_resampler_ccf(1, taps, FILTER_SIZE);
  d_resampled_input  = new gr_complex[static_cast<unsigned int>(d_conv_chunk*1.1)];
  d_freq_shift_input = new gr_complex[static_cast<unsigned int>(d_conv_chunk*1.1)]; 
      
  gr_complex* doppler_step_vector = static_cast<gr_complex*>(volk_gnsssdr_malloc(d_conv_chunk * sizeof(gr_complex), volk_gnsssdr_get_alignment()));
  
  float _phase[1] = {0};
  
  float phase_step_rad  = static_cast<float>(GPS_TWO_PI) * doppler_step / static_cast<float>(d_fs_in);
  volk_gnsssdr_s32f_sincos_32fc(doppler_step_vector, phase_step_rad, _phase, d_conv_chunk);

  d_opencl = init_opencl_environment("math_kernel.cl");

  // put doppler step vector into OpenCL buffer
  if (d_opencl == 0)
   {
     d_cl_queue->enqueueWriteBuffer(*(d_cl_doppler_step),
				 CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
				 doppler_step_vector);
   }
    
  volk_free(doppler_step_vector);

  for (unsigned int i =0;i < d_channels_count+d_conditioners_count;i++)
    {
      d_inputs.push_back(new gr_complex[d_conv_chunk]);
    }
      
}

/*
 * Our virtual destructor.
 */
passive_radar_cc::~passive_radar_cc()
{

  for (unsigned int i =0;i < d_inputs.size();i++)
    {
      delete [] d_inputs[i];
    }

  delete d_cl_queue;
  delete d_cl_in;
  delete d_cl_ffted_in;
  delete d_cl_magnitude;
  delete d_cl_doppler_step;
  delete d_cl_ffted_ref; 

  clFFT_DestroyPlan(d_cl_fft_plan);
  
  delete [] d_freq_shift_input;
  delete [] d_resampled_input;
  delete d_resamp;
}

static  const char source[] =
"kernel void mult_vec(global float *vec1,\n"
"		      global float *vec2)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if (i%2==0)\n"
"    {\n"
"      float a = vec1[i];\n"
"      float b = vec1[i+1];\n"
"      float c = vec2[i];\n"
"      float d = -vec2[i+1];\n"
"      vec1[i]   = a*c-b*d;\n"
"      vec1[i+1] = a*d+b*c;\n"		   
"    }\n"
"}\n"
"kernel void  magnitudes(global float *vec1,\n"
"			 global float *vec2)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if (i%2==0)\n"
"    {\n"
"      float a = vec1[i];\n"
"      float b = vec1[i+1];\n"
"      vec2[i/2]=a*a+b*b;\n"
"    }\n"
"}\n";

int passive_radar_cc::init_opencl_environment(std::string kernel_filename)
{
  //get all platforms (drivers)
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
      return 1;
    }

  d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_GPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
      return 2;
    }

  d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  d_cl_context = context;

  // std::cout << "Kernel code: \n" << kernel_code << std::endl;

  cl::Program::Sources sources;

  sources.push_back({source,strlen(source)});

  cl::Program program(context,sources);
  if(program.build(device)!=CL_SUCCESS)
    {
      std::cout << " Error building: "
		<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
		<< std::endl;
      return 3;
    }
  d_cl_program = program;

  // create buffers on the device

  d_cl_in           = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_ffted_in     = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_doppler_step = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_ffted_ref      = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_magnitude    = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_conv_chunk);

  //create queue to which we will push commands for the device.
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  //create FFT plan
  cl_int err;
  clFFT_Dim3 dim = {d_conv_chunk, 1, 1};

  d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  if (err != 0)
    {	        	      
      std::cout << "Error creating OpenCL FFT plan." << std::endl;
      return 4;
    }

  return 0;
}

std::vector<uint64_t> reliable_symbols;

int passive_radar_cc::work(int noutput_items __attribute__ ((unused)),
			   gr_vector_const_void_star &input_items,
			   gr_vector_void_star &output_items __attribute__ ((unused)))
{

  if (d_run_detector or d_opencl) return d_conv_chunk;
              
  for (unsigned int i =0;i < d_channels_count+d_conditioners_count;i++)
    {
      memcpy(d_inputs[i],(gr_complex*)input_items[i],d_conv_chunk*sizeof(gr_complex));
    }
  
  d_run_detector = true;
      
  std::thread([this]
	      {
		for (unsigned int ch =0;ch < d_channels_count;ch++)
		  {
		    if (reliable_symbols[ch] <  static_cast<unsigned int>
                                              (GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*GPS_CA_TELEMETRY_RATE_BITS_SECOND*d_duration)) continue;
					  
		    // here perform direct FFT for input_items[ch + d_conditioners_count]
		    
                    unsigned int id = ch + d_conditioners_count;
		    volk_32fc_conjugate_32fc(d_inputs[id],d_inputs[id],d_conv_chunk);

		    d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
						   sizeof(gr_complex)*d_conv_chunk, d_inputs[id]);

		    clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
					     clFFT_Forward, (*d_cl_ffted_ref)(), (*d_cl_ffted_ref)(),
					     0, NULL, NULL);
	  
		    for (unsigned int  step = 0;;step++) 
		      {

			if (step % d_resampling_step == 0)
			  {
				
			    gr_complex rem_phi[1]=gr_complex(1.0,0.0);
				
			    float doppler = static_cast<float>(step)*d_doppler_step - DOPPLER_RANGE;
			    if (doppler > DOPPLER_RANGE) break;
			    float phi  = static_cast<float>(GPS_TWO_PI) * doppler / static_cast<float>(d_fs_in);
			    gr_complex incm = std::exp(gr_complex(0,-phi));

                            // here correct  by doppler shift
			    volk_32fc_s32fc_x2_rotator_32fc(d_freq_shift_input, d_inputs[d_IDs[ch]],incm,rem_phi,d_conv_chunk);
				
			    d_resamp -> set_phase(0);
			    d_resamp -> set_rate(static_cast<float>(FILTER_SIZE)*(1 - doppler/GPS_L1_FREQ_HZ));
				
			    int nitems_read;
			    int processed = d_resamp->filter(d_resampled_input, d_freq_shift_input, d_conv_chunk, nitems_read);

			    for (int i = processed;i < d_conv_chunk;i++)
			      {
				d_resampled_input[i] =0;
			      }

			    d_cl_queue->enqueueWriteBuffer(*(d_cl_in),
							   CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
							   d_resampled_input);
			  }
			else
			  {
			    // here correct by doppler shift step

			    cl::Kernel kernel = cl::Kernel(d_cl_program, "mult_vect");
			    kernel.setArg(0, *d_cl_in); //input 1
			    kernel.setArg(1, *d_cl_doppler_step); //input 2
			    kernel.setArg(0, *d_cl_in); //output
			    d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk*2),
							     cl::NullRange);
			  }
			    
			// here perform  direct FFT 
			clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
						 clFFT_Forward, (*d_cl_in)(), (*d_cl_ffted_in)(),
						 0, NULL, NULL);
			    
			// here perform  element-wise production
			cl::Kernel kernel = cl::Kernel(d_cl_program, "mult_vect");
			kernel.setArg(0, *d_cl_ffted_in); //input 1
			kernel.setArg(1, *d_cl_ffted_ref); //input 2
			kernel.setArg(0, *d_cl_ffted_in); //output
			d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk*2),
							 cl::NullRange);

			// here perform  Inverse FFT
			clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
						 clFFT_Inverse, (*d_cl_ffted_in)(), (*d_cl_ffted_in)(),
						 0, NULL, NULL);
			    
			// Compute magnitude
			kernel = cl::Kernel(d_cl_program, "magnitudes");
			kernel.setArg(0, *d_cl_ffted_in);         //input 1
			kernel.setArg(1, *d_cl_magnitude); //output
			d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2),
							 cl::NullRange);

			//here put magnitudes to screen
		      }
		  }
        
		d_run_detector = false;
	      });
  // Tell runtime system how many output items we produced.
  return d_conv_chunk;
}



