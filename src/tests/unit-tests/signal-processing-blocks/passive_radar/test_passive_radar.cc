#include <gnuradio/sync_block.h>
#include <gnuradio/filter/pfb_arb_resampler_ccf.h>
#include <gnuradio/filter/pfb_arb_resampler.h>
#include <vector>
#include <fstream>
#include <string>
#include "fft_internal.h"
#include "fft_base_kernels.h"
#include <iostream>
#include <complex>
#include <volk_gnsssdr/volk_gnsssdr.h>
#include <volk/volk.h>

#ifdef __APPLE__
   #include "cl.hpp"
#else
    #include <cl.hpp>
#endif

class test_passive_radar_cc;

typedef boost::shared_ptr<test_passive_radar_cc>
               test_passive_radar_cc_sptr;

test_passive_radar_cc_sptr
make_test_passive_radar_cc(
                        float fs_in,
                        float duration,
                        unsigned int sources_count,
                        unsigned int channels_count,
                        unsigned int vector_length,
                        std::vector<unsigned int> IDs
                       );

class test_passive_radar_cc 
{
private:
  friend test_passive_radar_cc_sptr make_test_passive_radar_cc(
						     float fs_in,
						     float duration,
						     unsigned int sources_count,
						     unsigned int channels_count,
						     unsigned int vector_length,
						     std::vector<unsigned int> IDs
						     );

  unsigned int d_channels_count;
  unsigned int d_sources_count;
  float d_fs_in;
  unsigned int  d_conv_chunk ;
  unsigned int d_conditioners_count;
  unsigned int d_threshold;
  std::vector <unsigned int> d_IDs;
  std::vector <bool> d_reliable_channel_flags;
  bool d_run_detector;
  float d_doppler_step;
  float d_resampling_doppler_dist;
  float d_duration;
  gr::filter::kernel::pfb_arb_resampler_ccf *d_resamp;
  gr_complex* d_resampled_input;
  gr_complex* d_freq_shift_input;
  float * d_magnitudes;
  float * d_buffer_for_test;
  unsigned int d_resampling_step;
      
  int init_opencl_environment(std::string kernel_filename);

  cl::Platform d_cl_platform;
  cl::Device d_cl_device;
  cl::Context d_cl_context;
  cl::Program d_cl_program;
  cl::Buffer* d_cl_buffer_in;
      
  cl::Buffer* d_cl_buffer_magnitude;
  cl::CommandQueue* d_cl_queue;
  clFFT_Plan d_cl_fft_plan;
  cl_int d_cl_fft_batch_size;
  cl::Buffer*  d_cl_buffer_doppler_step;
      
  cl::Buffer* d_cl_buffer_fft_ref;
  cl::Buffer* d_cl_buffer_ffted_in;

  int d_opencl;
     
  gr_complex * d_doppler_step_vector;
          
  std::vector<gr_complex*> d_inputs;

  bool test(float* d_magnitudes,std::vector<gr_complex*>d_inputs,std::vector<unsigned int> d_IDs,
	    float doppler,unsigned int d_conditioners_count,unsigned int d_channels_count);
 
public:
  test_passive_radar_cc(
		   float fs_in,
		   float duration,
		   unsigned int sources_count,
		   unsigned int channels_count ,
		   unsigned int vector_length,
		   std::vector<unsigned int> IDs
		   );
  ~test_passive_radar_cc(); 

  // Where all the action really happens
  int work(int noutput_items,
	   gr_vector_const_void_star &input_items,
	   gr_vector_void_star &output_items);
};

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
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


static  const char source[] =
"kernel void mult_vec(global float *vec1,\n"
"		      global float *vec2)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if (i%2==0)\n"
"    {\n"
"      float a = vec1[i];\n"
"      float b = -vec1[i+1];\n"
"      float c = vec2[i];\n"
"      float d = vec2[i+1];\n"
"      vec2[i]   = a*c-b*d;\n"
"      vec2[i+1] = a*d+b*c;\n"		   
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
"}\n"
"kernel void conj(float *vec)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if (i%2==1)\n"
"    {\n"
"      vec[i] = -vec[i];\n"
"    }\n"
"}\n" ;

TEST(PassiveRadarTests,conv)
{
  unsigned int  d_conv_chunk = 8388608;

  gr_complex* d_input_a = (gr_complex*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  gr_complex* d_input_b = (gr_complex*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  float    * d_input_c = (float*) volk_malloc(sizeof(float)*d_conv_chunk,volk_get_alignment());

  for (unsigned int i=0;i < d_conv_chunk;i++)
    {
      d_input_a[i] = d_input_b[i] = 0;
    }

  d_input_a[0] = gr_complex(1,2);
  d_input_a[1] = gr_complex(3,-4);
  d_input_a[2] = gr_complex(-6,6);
  d_input_a[3] = gr_complex(0,3);

  d_input_b[d_conv_chunk-4] = gr_complex(1,2);
  d_input_b[d_conv_chunk-3] = gr_complex(3,-4);
  d_input_b[d_conv_chunk-2] = gr_complex(-6,6);
  d_input_b[d_conv_chunk-1] = gr_complex(0,3);
  
  cl::Platform d_cl_platform;
  cl::Device d_cl_device;
  cl::Context d_cl_context;
  cl::Program d_cl_program;
      
  cl::CommandQueue* d_cl_queue;
  clFFT_Plan d_cl_fft_plan;
  cl_int d_cl_fft_batch_size=1;

  cl::Buffer* d_cl_buffer_input_a;
  cl::Buffer* d_cl_buffer_input_b;
  cl::Buffer*  d_cl_buffer_input_c;   
    
 //get all platforms (drivers)
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  d_cl_context = context;

  cl::Program::Sources sources;

  sources.push_back({source,strlen(source)});

  cl::Program program(context,sources);
  if(program.build(device)!=CL_SUCCESS)
    {
      std::cout << " Error building: "
		<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
		<< std::endl;
    }
  d_cl_program = program;

  // create buffers on the device
  
  cl::Buffer* d_cl_sig       =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_ffted_sig =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_ffted_ref =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_powers    =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_conv_chunk);
 
  //create queue to which we will push commands for the device.
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device,0);

  //create FFT plan
  cl_int err;
  clFFT_Dim3 dim = {d_conv_chunk, 1, 1};

  d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);
  
   if (err != 0)
    {	
      delete d_cl_queue;
      delete d_cl_sig;       
      delete d_cl_ffted_sig;
      delete d_cl_ffted_ref;
      delete d_cl_powers;
        	      
      std::cout << "Error creating OpenCL FFT plan." << std::endl;
    }
   else
     {

       d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_sig, CL_TRUE, 0,
				      sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_b);

       cl::Kernel kernel = cl::Kernel(d_cl_program, "conj");
       kernel.setArg(0, *d_cl_ffted_ref); //input  0
       kernel.setArg(0, *d_cl_ffted_ref); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);

        d_cl_queue->enqueueReadBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       std::cout << "\n" << "conj_ref: " <<  '\n';
       for (unsigned int i=0;i < 4;i++)
	 {
	   std::cout << d_input_a[i] << " ";
	 }

       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_ref)(), (*d_cl_ffted_ref)(),
				0, NULL, NULL);

       d_cl_queue->enqueueReadBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       std::cout << "\n" << "ffted_ref: " <<  '\n';
       for (unsigned int i=0;i < 4;i++)
	 {
	   std::cout << d_input_a[i] << " ";
	 }

       d_cl_queue->enqueueReadBuffer(*d_cl_ffted_sig, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       std::cout << "\n" << "ffted_sig: " << '\n';
       for (unsigned int i=0;i < 4;i++)
	 {
	   std::cout << (d_input_a[i] )<< " ";
	 }

       kernel = cl::Kernel(d_cl_program, "mult_vec");
       kernel.setArg(1, *d_cl_ffted_sig); //input  0
       kernel.setArg(0, *d_cl_ffted_ref); // input 1
       kernel.setArg(1, *d_cl_ffted_sig); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);

       d_cl_queue->enqueueReadBuffer(*d_cl_ffted_sig, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       std::cout << "\n" << "conv_spec: " << '\n';
       for (unsigned int i=0;i < 4;i++)
	 {
	   std::cout << (d_input_a[i] )<< " ";
	 }

       // here perform  Inverse FFT
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Inverse, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       d_cl_queue->enqueueReadBuffer(*d_cl_ffted_sig, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       std::cout << "\n" << "inverse ffted_sig: "<< '\n';
       for (unsigned int i=0;i < 4;i++)
	 {	   
	   std::cout <<"(" << (real(d_input_a[i])/d_conv_chunk) << "," << (imag(d_input_a[i])/d_conv_chunk)<<") ";
	 }

       kernel = cl::Kernel(d_cl_program, "magnitudes");
       kernel.setArg(0, *d_cl_ffted_sig); //input  
       kernel.setArg(1, *d_cl_powers); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);

       d_cl_queue->enqueueReadBuffer(*d_cl_powers, CL_TRUE, 0,
				     sizeof(float)*d_conv_chunk,d_input_c);
       
       std::cout << '\n';
       for (unsigned int i=0;i < 4;i++)
	 {
	   std::cout << d_input_c[i] << " ";
	 }

       float m= -1;
       int ind =0;

       for (unsigned int i=0;i < d_conv_chunk;i++)
	 {
	   if (m<d_input_c[i])
	     {
	       m = d_input_c[i];
	       ind = i;
	     }	   
	 }
       
       std::cout << " ";
       std::cout << " ";

       std::cout << "m: " << sqrt(m)/(d_conv_chunk) << "\n";
       std::cout << "ind: " << ind << " ";

       delete d_cl_queue;
       delete d_cl_sig;       
       delete d_cl_ffted_sig;
       delete d_cl_ffted_ref;
       delete d_cl_powers;
     }

   clFFT_DestroyPlan(d_cl_fft_plan);
   volk_free(d_input_a);
   volk_free(d_input_b);
   volk_free(d_input_c);
}

TEST(PassiveRadarTests,conv2)
{
  unsigned int  d_conv_chunk = 8388608;

  gr_complex* d_input_a = (gr_complex*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  gr_complex* d_input_b = (gr_complex*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  float    * d_input_c = (float*) volk_malloc(sizeof(float)*d_conv_chunk,volk_get_alignment());

  for (unsigned int i=0;i < d_conv_chunk;i++)
    {
      d_input_a[i] = d_input_b[i] = 0;
    }

  d_input_a[0] = gr_complex(1,2);
  d_input_a[1] = gr_complex(3,-4);
  d_input_a[2] = gr_complex(-6,6);
  d_input_a[3] = gr_complex(0,3);

  d_input_b[d_conv_chunk-4] = gr_complex(1,2);
  d_input_b[d_conv_chunk-3] = gr_complex(3,-4);
  d_input_b[d_conv_chunk-2] = gr_complex(-6,6);
  d_input_b[d_conv_chunk-1] = gr_complex(0,3);
  
  cl::Platform d_cl_platform;
  cl::Device d_cl_device;
  cl::Context d_cl_context;
  cl::Program d_cl_program;
      
  cl::CommandQueue* d_cl_queue;
  clFFT_Plan d_cl_fft_plan;
  cl_int d_cl_fft_batch_size=1;

  cl::Buffer* d_cl_buffer_input_a;
  cl::Buffer* d_cl_buffer_input_b;
  cl::Buffer*  d_cl_buffer_input_c;   
    
 //get all platforms (drivers)
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  d_cl_context = context;

  cl::Program::Sources sources;

  sources.push_back({source,strlen(source)});

  cl::Program program(context,sources);
  if(program.build(device)!=CL_SUCCESS)
    {
      std::cout << " Error building: "
		<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
		<< std::endl;
    }
  d_cl_program = program;

  // create buffers on the device
  
  cl::Buffer* d_cl_sig       =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_ffted_sig =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_ffted_ref =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  cl::Buffer* d_cl_powers    =  new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_conv_chunk);
 
  //create queue to which we will push commands for the device.
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device,0);

  //create FFT plan
  cl_int err;
  clFFT_Dim3 dim = {d_conv_chunk, 1, 1};

  d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);
  
   if (err == 0)
     {

       d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_sig, CL_TRUE, 0,
				      sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_b);

       cl::Kernel kernel = cl::Kernel(d_cl_program, "conj");
       kernel.setArg(0, *d_cl_ffted_ref); //input  0
       kernel.setArg(0, *d_cl_ffted_ref); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);
       
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_ref)(), (*d_cl_ffted_ref)(),
				0, NULL, NULL);
       
       kernel = cl::Kernel(d_cl_program, "mult_vec");
       kernel.setArg(1, *d_cl_ffted_sig); //input  0
       kernel.setArg(0, *d_cl_ffted_ref); // input 1
       kernel.setArg(1, *d_cl_ffted_sig); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);

       // here perform  Inverse FFT
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Inverse, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       kernel = cl::Kernel(d_cl_program, "magnitudes");
       kernel.setArg(0, *d_cl_ffted_sig); //input  
       kernel.setArg(1, *d_cl_powers); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);
     }
   else
     {
       std::cout << "Error creating OpenCL FFT plan." << std::endl;
     }

   delete d_cl_queue;
   delete d_cl_sig;       
   delete d_cl_ffted_sig;
   delete d_cl_ffted_ref;
   delete d_cl_powers;

   clFFT_DestroyPlan(d_cl_fft_plan);
   volk_free(d_input_a);
   volk_free(d_input_b);
   volk_free(d_input_c);
}

TEST(PassiveRadarTests,gnsssdr_rot)
{
  unsigned int d_conv_chunk = 32;
  gr_complex* d_in = new gr_complex[d_conv_chunk];
  
  for (unsigned i =0;i < d_conv_chunk;i++)
    {
      d_in[i]=1;
    }
  
  d_in[0]=d_in[1]=1;
  gr_complex  incm = std::exp(gr_complex(0,0.01));
  gr_complex rem_phi[1]  = gr_complex (1,0);
  volk_32fc_s32fc_x2_rotator_32fc(d_in, d_in,incm,rem_phi,d_conv_chunk);

  for (unsigned int i =0;i < d_conv_chunk;i++)
    {
      std::cout << d_in[i] << " ";
    }
  delete [] d_in;
}

TEST(PassiveRadarTests,gnsssdr_conj)
{
  unsigned int d_conv_chunk = 2;
  gr_complex* d_in =new gr_complex[d_conv_chunk];// static_cast<gr_complex*>(volk_malloc( sizeof(gr_complex)*d_conv_chunk,volk_get_alignment()));
  d_in[0]=gr_complex(-1,-3);
  d_in[1]=gr_complex(1,10);
  gr_complex* d_out =new gr_complex[d_conv_chunk];// static_cast<gr_complex*>(volk_malloc( sizeof(gr_complex)*d_conv_chunk,volk_get_alignment()));
  volk_32fc_conjugate_32fc(d_in,d_in,d_conv_chunk);

  for (unsigned int i =0;i < 2;i++)
    {
      //std::cout << d_in[i] << " ";
      std::cout << d_in[i] << " ";
    }
  delete [] d_out;
  delete [] d_in;
}
