#include <gnuradio/sync_block.h>
#include <gnuradio/filter/pfb_arb_resampler_ccf.h>
#include <gnuradio/filter/pfb_arb_resampler.h>
#include <vector>
#include <fstream>
#include <string>
#include "fft_internal.h"
#include "fft_base_kernels.h"
#include <iostream>

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

const float DOPPLER_DEFINITION = 0.25;
const float MAX_TIME_SHIFT     = 0.1;
const float eps = std::numeric_limits<float>::epsilon();
const double GAIN = 1.0;
const double END_PASS_BAND = 0.44;
const double START_STOP_BAND = 0.49;
const double ATTENUATION = 20;
const float DOPPLER_RANGE = 5000;
gr::filter::firdes::win_type test_WINDOW = gr::filter::firdes::WIN_HAMMING;
unsigned int test_FILTER_SIZE = 32;

test_passive_radar_cc_sptr make_test_passive_radar_cc( 
					    float fs_in,
					    float duration,
					    unsigned int sources_count,
					    unsigned int channels_count,
					    unsigned int vector_length,
					    std::vector<unsigned int> IDs
					     )
{
  return test_passive_radar_cc_sptr (new test_passive_radar_cc(
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
test_passive_radar_cc::test_passive_radar_cc(
				   float fs_in,
				   float duration,
				   unsigned int sources_count,
				   unsigned int channels_count ,
				   unsigned int vector_length,
				   std::vector<unsigned int> IDs
				   ):
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
							   fs_in*test_FILTER_SIZE,
							   fs_in*END_PASS_BAND,
							   fs_in*(START_STOP_BAND-END_PASS_BAND),
							   ATTENUATION,
							   test_WINDOW
							   );
      
  d_resamp = new gr::filter::kernel::pfb_arb_resampler_ccf(1, taps, test_FILTER_SIZE);
  d_resampled_input  = new gr_complex[static_cast<unsigned int>(d_conv_chunk*1.1)];
  d_freq_shift_input = new gr_complex[static_cast<unsigned int>(d_conv_chunk*1.1)];
  d_magnitudes = new float[d_conv_chunk];
  d_buffer_for_test = new float[d_conv_chunk];
      
  gr_complex* doppler_step_vector = static_cast<gr_complex*>(volk_gnsssdr_malloc(d_conv_chunk * sizeof(gr_complex), volk_gnsssdr_get_alignment()));
  
  float _phase[1] = {0};
  
  float phase_step_rad  = static_cast<float>(GPS_TWO_PI) * doppler_step / static_cast<float>(d_fs_in);
  volk_gnsssdr_s32f_sincos_32fc(doppler_step_vector, - phase_step_rad, _phase, d_conv_chunk);

  d_opencl = init_opencl_environment("math_kernel.cl");

  // put doppler step vector into OpenCL buffer
  if (d_opencl == 0)
   {
     d_cl_queue->enqueueWriteBuffer(*(d_cl_buffer_doppler_step),
				 CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
				 doppler_step_vector);
   }
    
  delete [] doppler_step_vector;

  for (unsigned int i =0;i < d_channels_count+d_conditioners_count;i++)
    {
      d_inputs.push_back(new gr_complex[d_conv_chunk]);
    }
      
}

/*
 * Our virtual destructor.
 */
test_passive_radar_cc::~test_passive_radar_cc()
{

  for (unsigned int i =0;i < d_inputs.size();i++)
    {
      delete [] d_inputs[i];
    }

  if (d_opencl == 0)
    {
      delete d_cl_queue;
      delete d_cl_buffer_in;
      delete d_cl_buffer_ffted_in;
      delete d_cl_buffer_magnitude;
      delete d_cl_buffer_doppler_step;
      delete d_cl_buffer_fft_ref; 
    }

  clFFT_DestroyPlan(d_cl_fft_plan);
  
  delete [] d_freq_shift_input;
  delete [] d_resampled_input;
  delete d_resamp;
  delete [] d_magnitudes;
  delete [] d_buffer_for_test;
}

/*test(d_magnitudes,d_inputs,d_IDs,doppler,
  d_conditioners_count,d_channels_count) */

bool test_passive_radar_cc::test(float* d_magnitudes,std::vector<gr_complex*>d_inputs,
				 std::vector<unsigned int> d_IDs,float doppler,
				 unsigned int d_conditioners_count,unsigned int d_channels_count)
{

    
  return true;
}


int test_passive_radar_cc::init_opencl_environment(std::string kernel_filename)
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

  d_cl_buffer_in           = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_ffted_in     = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_doppler_step = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_fft_ref      = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_magnitude    = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(float)*d_conv_chunk);

  //create queue to which we will push commands for the device.
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  //create FFT plan
  cl_int err;
  clFFT_Dim3 dim = {d_conv_chunk, 1, 1};

  d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  if (err != 0)
    {	
      delete d_cl_queue;
      delete d_cl_buffer_in;
      delete d_cl_buffer_magnitude;
      delete d_cl_buffer_doppler_step;
      delete d_cl_buffer_fft_ref;
      delete d_cl_buffer_ffted_in;
        	      
      std::cout << "Error creating OpenCL FFT plan." << std::endl;
      return 4;
    }

  return 0;
}

std::vector<uint64_t> test_reliable_symbols;

TEST(PassiveRadarTests,OpenCl_Simple_Conv_Test)
{

  std::string kernel_filename ="math_kernel.cl"; //math_kernel.cl
  unsigned int  d_conv_chunk = 1024;

  gr_complex* d_input_a = new gr_complex[d_conv_chunk];
  gr_complex* d_input_b = new gr_complex[d_conv_chunk];
  float*      d_input_c = new float[d_conv_chunk];

  d_input_a[0] = -1;
  d_input_a[1] = -1;
  d_input_a[2] = 1;
  d_input_a[3] = 1;

  d_input_b[0] = 1;
  d_input_b[1] = 1;
  d_input_b[2] = -1;
  d_input_b[3] = -1;
  
  cl::Platform d_cl_platform;
  cl::Device d_cl_device;
  cl::Context d_cl_context;
  cl::Program d_cl_program;
      
  cl::CommandQueue* d_cl_queue;
  clFFT_Plan d_cl_fft_plan;
  cl_int d_cl_fft_batch_size=0;

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
    }
  d_cl_program = program;

  // create buffers on the device
  
  d_cl_buffer_input_a = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_input_b = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
  d_cl_buffer_input_c = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_conv_chunk);
 
  //create queue to which we will push commands for the device.
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  //create FFT plan
  cl_int err;
  clFFT_Dim3 dim = {d_conv_chunk, 1, 1};

  d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_input_a, CL_TRUE, 0,
						   sizeof(gr_complex)*d_conv_chunk, d_input_a);

   if (err != 0)
    {	
      delete d_cl_queue;
      delete d_cl_buffer_input_a;
      delete d_cl_buffer_input_b;
      delete d_cl_buffer_input_c;
        	      
      std::cout << "Error creating OpenCL FFT plan." << std::endl;
    }
   else
     {

       d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_input_a, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_a);
       
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_buffer_input_a)(), (*d_cl_buffer_input_a)(),
				0, NULL, NULL);

       //Conjugate the local code
       cl::Kernel kernel = cl::Kernel(d_cl_program, "conj_vector");
       kernel.setArg(0, *d_cl_buffer_input_a); //input
       kernel.setArg(1, *d_cl_buffer_input_a); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk), cl::NullRange);

       d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_input_b, CL_TRUE, 0,
				      sizeof(gr_complex)*d_conv_chunk, d_input_b);

       d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_input_b, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_b);

       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_buffer_input_b)(), (*d_cl_buffer_input_b)(),
				0, NULL, NULL);

       kernel = cl::Kernel(d_cl_program, "mult_vectors");
       kernel.setArg(0, *d_cl_buffer_input_a); //input 1
       kernel.setArg(1, *d_cl_buffer_input_b); //input 2
       kernel.setArg(2, *d_cl_buffer_input_b); //output
       d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk),
					cl::NullRange);

       // here perform  Inverse FFT
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Inverse, (*d_cl_buffer_input_b)(), (*d_cl_buffer_input_b)(),
				0, NULL, NULL);

       // Compute magnitude
       kernel = cl::Kernel(d_cl_program, "magnitude_squared");
       kernel.setArg(0, *d_cl_buffer_input_b);         //input 1
       kernel.setArg(1, *d_cl_buffer_input_c); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk),
					cl::NullRange);

       d_cl_queue->enqueueReadBuffer(*d_cl_buffer_input_c, CL_TRUE, 0,
				     sizeof(float)*d_conv_chunk,d_input_c);

       for (unsigned int i=0;i < d_conv_chunk;i++)
	 {
	   std::cout << d_input_a[i] << " ";
	 }

       std::cout << '\n';
       for (unsigned int i=0;i < d_conv_chunk;i++)
	 {
	   std::cout << d_input_c[i] << " ";
	 }

       delete d_cl_queue;
       delete d_cl_buffer_input_a;
       delete d_cl_buffer_input_b;
       delete d_cl_buffer_input_c;
     }

  delete [] d_input_a;
  delete [] d_input_b;
  delete [] d_input_c;
}


TEST(PassiveRadarTests,cl_buf_read_write)
{

  unsigned int d_test_sz = 4;
  gr_complex* d_in = new gr_complex[d_test_sz];

  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  cl::Platform d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  cl::Device d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  cl::Context d_cl_context = context;
 
  cl::Buffer*  d_cl_buf_in = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_test_sz);

  d_in[0] = -1;
  d_in[1] = -1;
  d_in[2] = 1;
  d_in[3] = 1;

  cl::CommandQueue* d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  d_cl_queue->enqueueWriteBuffer(*d_cl_buf_in, CL_TRUE, 0,
				 sizeof(gr_complex)*d_test_sz, d_in);

  for (unsigned int i =0;i < d_test_sz;i++)
    {
      d_in[i]=0;
    }

  d_cl_queue->enqueueReadBuffer(*d_cl_buf_in, CL_TRUE, 0,
				     sizeof(float)*d_test_sz,d_in);

  for (unsigned int i =0;i < d_test_sz;i++)
    {
      std::cout << d_in[i] << " ";
    }

  delete [] d_in;
  delete d_cl_buf_in;
  delete d_cl_queue;
  
}

TEST(PassiveRadarTests,cl_forward_fft)
{
  unsigned int d_test_sz = 4;
  gr_complex* d_in = new gr_complex[d_test_sz];

  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  cl::Platform d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  cl::Device d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  cl::Context d_cl_context = context;
 
  cl::Buffer*  d_cl_buf_in = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_test_sz);

  d_in[0] = -1;
  d_in[1] = -1;
  d_in[2] = 1;
  d_in[3] = 1;

  cl::CommandQueue* d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  cl_int err;
  clFFT_Dim3 dim = {d_test_sz, 1, 1};

  clFFT_Plan d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  d_cl_queue->enqueueWriteBuffer(*d_cl_buf_in, CL_TRUE, 0,
				 sizeof(gr_complex)*d_test_sz, d_in);

  cl_int d_cl_fft_batch_size = 1;

  clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_buf_in)(), (*d_cl_buf_in)(),
				0, NULL, NULL);

  d_cl_queue->enqueueReadBuffer(*d_cl_buf_in, CL_TRUE, 0,
				     sizeof(float)*d_test_sz,d_in);

  for (unsigned int i =0;i < d_test_sz;i++)
    {
      std::cout << d_in[i] << " ";
    }
  
  clFFT_DestroyPlan(d_cl_fft_plan);
  delete [] d_in;
  delete d_cl_buf_in;
  delete d_cl_queue;
}

TEST(PassiveRadarTests,cl_forward_fft_batch_size_zero)
{
  unsigned int d_test_sz = 4;
  gr_complex* d_in = new gr_complex[d_test_sz];

  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  cl::Platform d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  cl::Device d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  cl::Context d_cl_context = context;
 
  cl::Buffer*  d_cl_buf_in = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_test_sz);

  d_in[0] = -1;
  d_in[1] = -1;
  d_in[2] = 1;
  d_in[3] = 1;

  cl::CommandQueue* d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  cl_int err;
  clFFT_Dim3 dim = {d_test_sz, 1, 1};

  clFFT_Plan d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  d_cl_queue->enqueueWriteBuffer(*d_cl_buf_in, CL_TRUE, 0,
				 sizeof(gr_complex)*d_test_sz, d_in);

  cl_int d_cl_fft_batch_size = 0;

  clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_buf_in)(), (*d_cl_buf_in)(),
				0, NULL, NULL);

  d_cl_queue->enqueueReadBuffer(*d_cl_buf_in, CL_TRUE, 0,
				     sizeof(float)*d_test_sz,d_in);

  for (unsigned int i =0;i < d_test_sz;i++)
    {
      std::cout << d_in[i] << " ";
    }
  
  clFFT_DestroyPlan(d_cl_fft_plan);
  delete [] d_in;
  delete d_cl_buf_in;
  delete d_cl_queue;
}

TEST(PassiveRadarTests,cl_forward_inverse)
{
  unsigned int d_test_sz = 1024;
  gr_complex* d_in = new gr_complex[d_test_sz];

  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);

  if(all_platforms.size()==0)
    {
      std::cout << "No OpenCL platforms found. Check OpenCL installation!" << std::endl;
    }

  cl::Platform d_cl_platform = all_platforms[0]; //get default platform
  std::cout << "Using platform: " << d_cl_platform.getInfo<CL_PLATFORM_NAME>()
	    << std::endl;

  //get default GPU device of the default platform
  std::vector<cl::Device> gpu_devices;
  d_cl_platform.getDevices(CL_DEVICE_TYPE_CPU, &gpu_devices);

  if(gpu_devices.size()==0)
    {
      std::cout << "No GPU devices found. Check OpenCL installation!" << std::endl;
    }

  cl::Device d_cl_device = gpu_devices[0];

  std::vector<cl::Device> device;
  device.push_back(d_cl_device);
  std::cout << "Using device: " << d_cl_device.getInfo<CL_DEVICE_NAME>() << std::endl;

  cl::Context context(device);
  cl::Context d_cl_context = context;
 
  cl::Buffer*  d_cl_buf_in = new cl::Buffer(d_cl_context, CL_MEM_READ_WRITE, sizeof(gr_complex)*d_test_sz);

  d_in[0] = -1;
  d_in[1] = 3;
  d_in[2] = 100;
  d_in[3] = 10;

  cl::CommandQueue* d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

  cl_int err;
  clFFT_Dim3 dim = {d_test_sz, 1, 1};

  clFFT_Plan d_cl_fft_plan = clFFT_CreatePlan(d_cl_context(), dim, clFFT_1D,
				   clFFT_InterleavedComplexFormat, &err);

  d_cl_queue->enqueueWriteBuffer(*d_cl_buf_in, CL_TRUE, 0,
				 sizeof(gr_complex)*d_test_sz, d_in);

  cl_int d_cl_fft_batch_size = 1;

  for (unsigned int i=0;i < d_test_sz;i++)
	 {
	   std::cout << d_in[i] << " ";
	 }

       std::cout << '\n';

  clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_buf_in)(), (*d_cl_buf_in)(),
				0, NULL, NULL);

  d_cl_queue->enqueueReadBuffer(*d_cl_buf_in, CL_TRUE, 0,
				     sizeof(gr_complex)*d_test_sz,d_in);

  for (unsigned int i=0;i < d_test_sz;i++)
	 {
	   std::cout << d_in[i] << " ";
	 }

  std::cout << '\n';

  clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Inverse, (*d_cl_buf_in)(), (*d_cl_buf_in)(),
				0, NULL, NULL);

  d_cl_queue->enqueueReadBuffer(*d_cl_buf_in, CL_TRUE, 0,
				     sizeof(gr_complex)*d_test_sz,d_in);

  for (unsigned int i =0;i < d_test_sz;i++)
    {
      std::cout << d_in[i] << " ";
    }

  
  clFFT_DestroyPlan(d_cl_fft_plan);
  delete [] d_in;
  delete d_cl_buf_in;
  delete d_cl_queue;
}

static  const char source[] =
"kernel void conj_vector(ulong n,\n"
"			 global float *vec1,\n"
"		         global float *vec2)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if ((i%2==0) && (i < n))\n"
"    {\n"
"      float a = vec1[i];\n"
"      float b = vec1[i+1];\n"
"      float c = vec2[i];\n"
"      float d = -vec2[i+1];\n"
"      vec2[i]   = a*c-b*d;\n"
"      vec2[i+1] = a*d+b*c;\n"		   
"    }\n"
"}\n"
"kernel void  magnitudes(ulong n,\n"
"			global float *vec1,\n"
"			global float *vec2)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if ((i%2==0) && (i<n))\n"
"    {\n"
"      float a = vec1[i];\n"
"      float b = vec1[i+1];\n"
"      vec2[i/2]=a*a+b*b;\n"
"    }\n"
"}\n"
"kernel void freq_shift(ulong n,\n"
"		       float phase,\n"
"		       global float *in,\n"
"		       global float *out)\n"
"{\n"
"  size_t i = get_global_id(0);\n"
"  if ((i%2==0) && (i<n))\n"
"    {\n"
"      float a =  in[i];\n"
"      float b =  in[i+1];\n"
"      float c =  cos(phase*0.5*i);\n"
"      float d = -sin(phase*0.5*i);\n"
"      out[i]    =  a*c-b*d;\n"
"      out[i+1]  =  a*d+b*c;\n"
"    }\n"
"}\n";

TEST(PassiveRadarTests,conv)
{
  std::string kernel_filename ="math_kernel.cl"; //math_kernel.cl
  unsigned int  d_conv_chunk = 4;

  lv_32fc_t* d_input_a = (lv_32fc_t*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  lv_32fc_t* d_input_b = (lv_32fc_t*) volk_malloc(sizeof(lv_32fc_t)*d_conv_chunk,volk_get_alignment());
  float    * d_input_c = (float*) volk_malloc(sizeof(float)*d_conv_chunk,volk_get_alignment());

  d_input_a[0] = gr_complex(1,0);
  d_input_a[1] = gr_complex(3,0);
  d_input_a[2] = gr_complex(-6,0);
  d_input_a[3] = gr_complex(0,0);

  d_input_b[d_conv_chunk-4] = 0;
  d_input_b[d_conv_chunk-3] = -6;
  d_input_b[d_conv_chunk-2] = 3;
  d_input_b[d_conv_chunk-1] = 1;
  
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

  // build the program from the source in the file
  std::ifstream kernel_file(kernel_filename, std::ifstream::in);
  std::string kernel_code(std::istreambuf_iterator<char>(kernel_file),
			  (std::istreambuf_iterator<char>()));
  kernel_file.close();

  // std::cout << "Kernel code: \n" << kernel_code << std::endl;

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
  d_cl_queue = new cl::CommandQueue(d_cl_context,d_cl_device);

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

       float phase =1;
       
       cl::Kernel kernel;// = cl::Kernel(d_cl_program, "freq_shift");
	 /*kernel.setArg(0,static_cast<cl_ulong> (d_conv_chunk*2));
       kernel.setArg(1,phase);//input  0
       kernel.setArg(2, *d_cl_sig); //input  1
       kernel.setArg(3, *d_cl_ffted_sig); // output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);*/
       
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       d_cl_queue->enqueueWriteBuffer(*d_cl_ffted_ref, CL_TRUE, 0,
				     sizeof(gr_complex)*d_conv_chunk,d_input_b);

       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Forward, (*d_cl_ffted_ref)(), (*d_cl_ffted_ref)(),
				0, NULL, NULL);

       kernel = cl::Kernel(d_cl_program, "conj_vector");
       kernel.setArg(0,static_cast<cl_ulong> (d_conv_chunk*2));
       kernel.setArg(1, *d_cl_ffted_sig); //input  0
       kernel.setArg(2, *d_cl_ffted_ref); // input 1
       kernel.setArg(2, *d_cl_ffted_sig); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk*2), cl::NullRange);

       // here perform  Inverse FFT
       clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
				clFFT_Inverse, (*d_cl_ffted_sig)(), (*d_cl_ffted_sig)(),
				0, NULL, NULL);

       kernel = cl::Kernel(d_cl_program, "magnitudes");
       kernel.setArg(0,static_cast<cl_ulong> (d_conv_chunk*2));
       kernel.setArg(1, *d_cl_ffted_sig); //input  
       kernel.setArg(2, *d_cl_powers); //output
       d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk), cl::NullRange);

       d_cl_queue->enqueueReadBuffer(*d_cl_powers, CL_TRUE, 0,
				     sizeof(float)*d_conv_chunk,d_input_c);
       
       std::cout << '\n';
       for (unsigned int i=0;i < d_conv_chunk;i++)
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

       std::cout << "m: " << m << "\n";
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
