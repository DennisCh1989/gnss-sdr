/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
	d_channels_count(channels_count),
        d_duration(duration)
    {
      d_conv_chunk = static_cast<unsigned int> (duration * fs_in);
      d_IDs = IDs;
      d_run_detector = false;
      d_doppler_range = -5000;
      d_doppler_step = (1/duration)*DOPPLER_DEFINITION;
      d_resampling_doppler_dist =MAX_TIME_SHIFT/(GPS_L1_CA_CODE_RATE_HZ*duration) *GPS_L1_FREQ_HZ;
      d_resampling_step = static_cast<unsigned int> ((d_resampling_doppler_dist+eps)/d_doppler_step);
      d_min_reliable_symbols = static_cast<unsigned int>
	(GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*GPS_CA_TELEMETRY_RATE_BITS_SECOND*d_duration);
           
      std::vector<float> taps = gr::filter::firdes::low_pass_2(
							     GAIN,
							     fs_in*FILTER_SIZE,
							     fs_in*END_PASS_BAND,
							     fs_in*(START_STOP_BAND-END_PASS_BAND),
							     ATTENUATION,
							     WINDOW
							     );
      
      d_resamp = new gr::filter::kernel::pfb_arb_resampler_ccf(1, taps, FILTER_SIZE);
      float max_chip_rate_err = d_doppler_range/GPS_L1_FREQ_HZ; 
      d_resampled_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]);
      d_freq_shift_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]); 
      unsigned int d_vector_length = static_cast<unsigned int> (fs_in / (GPS_L1_CA_CODE_RATE_HZ / GPS_L1_CA_CODE_LENGTH_CHIPS))*GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*2;

      d_fft_size_pow2 = pow(2, ceil(log2(2 * d_conv_chunk)));      
      d_doppler_step_vector = static_cast<gr_complex*>(volk_gnsssdr_malloc(d_fft_size_pow2 * sizeof(gr_complex), volk_gnsssdr_get_alignment()));
      d_doppler_minus_range = static_cast<gr_complex*>(volk_gnsssdr_malloc(d_fft_size_pow2 * sizeof(gr_complex), volk_gnsssdr_get_alignment()));
      d_zero_vector = static_cast<gr_complex*>(volk_gnsssdr_malloc((d_fft_size_pow2 - d_conv_chunk) * sizeof(gr_complex), volk_gnsssdr_get_alignment()));

      float _phase[1] = {0};
      
      float phase_rad_minus_range  = static_cast<float>(GPS_TWO_PI) * (d_doppler_range) / static_cast<float>(d_fs_in); 
      volk_gnsssdr_s32f_sincos_32fc(d_doppler_minus_range, -phase_rad_minus_range, _phase, d_conv_chunk);

      float phase_step_rad  = static_cast<float>(GPS_TWO_PI) * (d_doppler_step) / static_cast<float>(d_fs_in);
      volk_gnsssdr_s32f_sincos_32fc(d_doppler_step_vector, - phase_step_rad, _phase, d_conv_chunk);


      // put doppler step vector into OpenCL buffer
      d_cl_queue->enqueueWriteBuffer(*(d_cl_buffer_doppler_step),
				     CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
				     d_doppler_step_vector);
      
      set_history(d_vector_length);
    }

    /*
     * Our virtual destructor.
     */
    passive_radar_cc::~passive_radar_cc()
    {
    }


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

    		// build the program from the source in the file
    		std::ifstream kernel_file(kernel_filename, std::ifstream::in);
    		std::string kernel_code(std::istreambuf_iterator<char>(kernel_file),
        		(std::istreambuf_iterator<char>()));
    		kernel_file.close();

    		// std::cout << "Kernel code: \n" << kernel_code << std::endl;

    		cl::Program::Sources sources;

    		sources.push_back({kernel_code.c_str(),kernel_code.length()});

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

                const int d_fft_size =1;
                const int d_fft_size_pow2 = 1;
    		d_cl_buffer_in = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_fft_size);
    		d_cl_buffer_fft_codes = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_fft_size_pow2);
    		d_cl_buffer_1 = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_fft_size_pow2);
    		d_cl_buffer_2 = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_fft_size_pow2);
    		d_cl_buffer_magnitude = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_fft_size);
		d_cl_buffer_doppler_step = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_conv_chunk);

    		//create queue to which we will push commands for the device.
    		d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

    		//create FFT plan
    		cl_int err;
    		clFFT_Dim3 dim = {d_fft_size_pow2, 1, 1};

    		d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
        		                             clFFT_InterleavedComplexFormat, &err);

    		if (err != 0)
    		 {	
        		delete d_cl_queue;
        		delete d_cl_buffer_in;
        		delete d_cl_buffer_1;
        		delete d_cl_buffer_2;
        		delete d_cl_buffer_magnitude;
        		delete d_cl_buffer_fft_codes;

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
      d_run_detector = true;
      std::thread([this,input_items]
		  {
		    for (unsigned ch =0;ch < d_channels_count;ch++)
		      {
			if (reliable_symbols[ch] < d_min_reliable_symbols) continue;

			gr_complex *in  = (gr_complex*) input_items[d_IDs[ch]];
			gr_complex *ref = (gr_complex*) input_items[ch + d_conditioners_count];
					  
			// here perform direct FFT for input_items[ch + d_conditioners_count]

			d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_2, CL_TRUE, 0,
						       sizeof(gr_complex)*d_conv_chunk, ref);

			d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_2, CL_TRUE, sizeof(gr_complex)*d_conv_chunk,
						       sizeof(gr_complex)*(d_fft_size_pow2 - d_conv_chunk),
						       d_zero_vector);

			clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
						 clFFT_Forward, (*d_cl_buffer_2)(), (*d_cl_buffer_2)(),
						 0, NULL, NULL);

			//Conjugate the local code
			cl::Kernel kernel = cl::Kernel(d_cl_program, "conj_vector");
			kernel.setArg(0, *d_cl_buffer_2);         //input
			kernel.setArg(1, *d_cl_buffer_fft_codes); //output
			d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_fft_size_pow2), cl::NullRange);

			// initialize input vector
			d_cl_queue->enqueueWriteBuffer(*(d_cl_buffer_in),
						       CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
						       d_doppler_minus_range);

			float doppler = - d_doppler_range;
	  
			for (unsigned int  step = 0;step< d_doppler_range;step++) 
			  {

			    // here correct  d_freq_shift_doppler by doppler shift

			    kernel = cl::Kernel(d_cl_program, "mult_vectors");
			    kernel.setArg(0, *d_cl_buffer_in); //input 1
			    kernel.setArg(1, *d_cl_buffer_doppler_step); //input 2
			    kernel.setArg(2, *d_cl_buffer_1); //output
			    d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk),
							     cl::NullRange);

			    if (step % d_resampling_step == 0)
			      {
				
				d_resamp -> set_phase(0);
				d_resamp -> set_rate(static_cast<float>(FILTER_SIZE)*(1 - doppler/GPS_L1_FREQ_HZ));
				
				int nitems_read;
				int processed = d_resamp->filter(d_resampled_input.get(), in, d_conv_chunk, nitems_read);

				for (int i = processed;i < d_conv_chunk;i++)
				  {
				    d_resampled_input.get()[i] =0;
				  }

				// here correct  d_freq_shift_doppler by doppler shift

				d_cl_queue->enqueueWriteBuffer(*(d_cl_buffer_in),
							       CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
							       d_doppler_minus_range);
			      }

			    memcpy(d_freq_shift_input.get(), d_resampled_input.get(), sizeof(gr_complex)*d_conv_chunk);
			    			    
			    // here perform  direct FFT for d_freq_shift_doppler
			    // here perform  element-wise production d_freq_shift_doppler with FFT(input_items[ch])
			    // here perform  Inverse FFT
			    // here get magnitudes

			    doppler+=d_doppler_step;
			  }
		      }
        
		    d_run_detector = false;
		  });
      // Tell runtime system how many output items we produced.
      return d_conv_chunk;
    }


