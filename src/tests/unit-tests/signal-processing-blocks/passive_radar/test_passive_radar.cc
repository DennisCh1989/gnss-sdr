#include <gnuradio/sync_block.h>
#include <gnuradio/filter/pfb_arb_resampler_ccf.h>
#include <gnuradio/filter/pfb_arb_resampler.h>
#include <vector>
#include <fstream>
#include <string>
#include "fft_internal.h"
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

int test_passive_radar_cc::work(int noutput_items __attribute__ ((unused)),
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
		    if (test_reliable_symbols[ch] <  static_cast<unsigned int>
                                              (GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*GPS_CA_TELEMETRY_RATE_BITS_SECOND*d_duration)) continue;

                    for (unsigned int i =0;i < d_conv_chunk/2;i++)
                      {
                         gr_complex buf                                          = d_inputs[ch+d_conditioners_count][i];
                         d_inputs[ch+d_conditioners_count] [i]                   = d_inputs[ch+d_conditioners_count][d_conv_chunk -1 - i];
                         d_inputs[ch+d_conditioners_count] [d_conv_chunk -1 - i] = buf;
		      }
					  
		    // here perform direct FFT for input_items[ch + d_conditioners_count]

		    d_cl_queue->enqueueWriteBuffer(*d_cl_buffer_fft_ref, CL_TRUE, 0,
						   sizeof(gr_complex)*d_conv_chunk, d_inputs[ch + d_conditioners_count]);

		    clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
					     clFFT_Forward, (*d_cl_buffer_fft_ref)(), (*d_cl_buffer_fft_ref)(),
					     0, NULL, NULL);

		    //Conjugate the local code
		    cl::Kernel kernel = cl::Kernel(d_cl_program, "conj_vector");
		    kernel.setArg(0, *d_cl_buffer_fft_ref); //input
		    kernel.setArg(1, *d_cl_buffer_fft_ref); //output
		    d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk), cl::NullRange);
	  
		    for (unsigned int  step = 0;;step++) 
		      {

			float doppler = static_cast<float>(step)*d_doppler_step - DOPPLER_RANGE;
			if (step % d_resampling_step == 0)
			  {
				
			    gr_complex _phase[1];
			    _phase[0] = gr_complex(0.0,0.0);
				
			    if (doppler > DOPPLER_RANGE) break;
			    float phase_inc_f = static_cast<float>(GPS_TWO_PI) * doppler / static_cast<float>(d_fs_in);
			    gr_complex phase_inc = std::exp(gr_complex(0,-phase_inc_f));

                            // here correct  by doppler shift
			    volk_32fc_s32fc_x2_rotator_32fc(d_freq_shift_input, d_inputs[d_IDs[ch]],phase_inc,_phase,d_conv_chunk);
				
			    d_resamp -> set_phase(0);
			    d_resamp -> set_rate(static_cast<float>(test_FILTER_SIZE)*(1 - doppler/GPS_L1_FREQ_HZ));
				
			    int nitems_read;
			    int processed = d_resamp->filter(d_resampled_input, d_freq_shift_input, d_conv_chunk, nitems_read);

			    for (int i = processed;i < d_conv_chunk;i++)
			      {
				d_resampled_input[i] =0;
			      }

			    d_cl_queue->enqueueWriteBuffer(*(d_cl_buffer_in),
							   CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
							   d_resampled_input);
			  }
			else
			  {
			    // here correct by doppler shift step

			    kernel = cl::Kernel(d_cl_program, "mult_vectors");
			    kernel.setArg(0, *d_cl_buffer_in); //input 1
			    kernel.setArg(1, *d_cl_buffer_doppler_step); //input 2
			    kernel.setArg(2, *d_cl_buffer_in); //output
			    d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk),
							     cl::NullRange);
			  }
			    
			// here perform  direct FFT 
			clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
						 clFFT_Forward, (*d_cl_buffer_in)(), (*d_cl_buffer_ffted_in)(),
						 0, NULL, NULL);
			    
			// here perform  element-wise production
			kernel = cl::Kernel(d_cl_program, "mult_vectors");
			kernel.setArg(0, *d_cl_buffer_ffted_in); //input 1
			kernel.setArg(1, *d_cl_buffer_fft_ref); //input 2
			kernel.setArg(2, *d_cl_buffer_ffted_in); //output
			d_cl_queue->enqueueNDRangeKernel(kernel,cl::NullRange, cl::NDRange(d_conv_chunk),
							 cl::NullRange);

			// here perform  Inverse FFT
			clFFT_ExecuteInterleaved((*d_cl_queue)(), d_cl_fft_plan, d_cl_fft_batch_size,
						 clFFT_Inverse, (*d_cl_buffer_ffted_in)(), (*d_cl_buffer_ffted_in)(),
						 0, NULL, NULL);
			    
			// Compute magnitude
			kernel = cl::Kernel(d_cl_program, "magnitude_squared");
			kernel.setArg(0, *d_cl_buffer_ffted_in);         //input 1
			kernel.setArg(1, *d_cl_buffer_magnitude); //output
			d_cl_queue->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(d_conv_chunk),
							 cl::NullRange);

			//here put magnitudes to screen
			d_cl_queue->enqueueReadBuffer(*(d_cl_buffer_magnitude),
						      CL_TRUE, 0, sizeof(gr_complex)*d_conv_chunk,
						      d_magnitudes);
			
			//test function

			if (test(d_magnitudes,d_inputs,d_IDs,doppler,
				 d_conditioners_count,d_channels_count) == false)
			  {
			    return -1;
			  }
		      }
		  }
        
		d_run_detector = false;
	      });
  // Tell runtime system how many output items we produced.
  return d_conv_chunk;
}


TEST(PassiveRadarTests,Test1)
{
  
  const unsigned int d_sources_count = 2;
  const unsigned int d_channels_count = 3;
  std::vector <unsigned int> d_IDs={0,0,1};

  unsigned int d_conv_chunk = 1024;

  //generate first src vec

  
  gr_vector_const_void_star input_items;

  //generate sources: src1 src2 
  for (unsigned int i =0;i <d_sources_count;i++)
    {
      input_items.push_back(new gr_complex[d_conv_chunk]);
    }

  //connect sources with  other inputs

  for (unsigned int  i=0;i < d_channels_count;i++)
    {
        input_items.push_back(input_items[d_IDs[i]]);
    }

  /*
    test_passive_radar_cc(
    float fs_in,
    float duration,
    unsigned int sources_count,
    unsigned int channels_count ,
    unsigned int vector_length,
    std::vector<unsigned int> IDs
    );
   */


  float d_fs_in = 4000000;
  float d_duration = 0.000256; // sec d_duration = d_conv_chunk/d_fs_in
  unsigned int d_vector_length = 0; //unused
  
  test_passive_radar_cc_sptr radar = make_test_passive_radar_cc(d_fs_in,d_duration,d_sources_count,d_channels_count,d_vector_length,d_IDs);

  gr_vector_void_star output_items;

  int noutput_items=0; //unused
  EXPECT_GT(radar->work(noutput_items,input_items,output_items),0);
}

TEST(PassiveRadarTests,OpenCl_Simple_Conv_Test)
{

  std::string kernel_filename ="";
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
  cl_int d_cl_fft_batch_size;

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
  d_cl_platform.getDevices(CL_DEVICE_TYPE_GPU, &gpu_devices);

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
