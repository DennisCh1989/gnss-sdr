/* -*- c++ -*- */
/* 
 * Copyright 2018 Dennis Chuprakov.
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

#ifndef INCLUDED_PASSIVE_RADAR_CC_H
#define INCLUDED_PASSIVE_RADAR_CC_H

#include <gnuradio/sync_block.h>
#include <gnuradio/filter/pfb_arb_resampler_ccf.h>
#include <gnuradio/filter/pfb_arb_resampler.h>
#include <vector>
#include <fstream>
#include <string>
#include "fft_internal.h"

#ifdef __APPLE__
   #include "cl.hpp"
#else
    #include <cl.hpp>
#endif

class passive_radar_cc;

typedef boost::shared_ptr<passive_radar_cc>
               passive_radar_cc_sptr;

passive_radar_cc_sptr
make_passive_radar_cc(
                        float fs_in,
                        float duration,
                        unsigned int sources_count,
                        unsigned int channels_count,
                        unsigned int vector_length,
                        std::vector<unsigned int> IDs
                       );

    class passive_radar_cc : public gr::sync_block
    {
     private:
      friend passive_radar_cc_sptr make_passive_radar_cc(
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
      float d_doppler_range;
      float d_doppler_step;
      float d_resampling_doppler_dist;
      float d_duration;
      gr::filter::kernel::pfb_arb_resampler_ccf *d_resamp;
      std::shared_ptr<gr_complex> d_resampled_input;
      std::shared_ptr<gr_complex> d_freq_shift_input; 
      unsigned int d_vector_length;
      unsigned int d_resampling_step;
      unsigned int d_min_reliable_symbols;

      int init_opencl_environment(std::string kernel_filename);

      cl::Platform d_cl_platform;
      cl::Device d_cl_device;
      cl::Context d_cl_context;
      cl::Program d_cl_program;
      cl::Buffer* d_cl_buffer_in;
      cl::Buffer* d_cl_buffer_fft_codes;
      cl::Buffer* d_cl_buffer_1;
      cl::Buffer* d_cl_buffer_2;
      cl::Buffer* d_cl_buffer_magnitude;
      cl::Buffer** d_cl_buffer_grid_doppler_wipeoffs;
      cl::CommandQueue* d_cl_queue;
      clFFT_Plan d_cl_fft_plan;
      cl_int d_cl_fft_batch_size;
      cl::Buffer*  d_cl_buffer_doppler_step;
      cl::Buffer*  d_cl_buffer_doppler;

      int d_opencl;

      unsigned int  d_fft_size_pow2;      
      gr_complex * d_doppler_step_vector;
      gr_complex * d_doppler_minus_range;
      gr_complex * d_zero_vector;

     public:
      passive_radar_cc(
                        float fs_in,
                        float duration,
                        unsigned int sources_count,
                        unsigned int channels_count ,
                        unsigned int vector_length,
                        std::vector<unsigned int> IDs
                         );
      ~passive_radar_cc(); 

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };


#endif /* INCLUDED_PASSIVE_RADAR_PASSIVE_RADAR_IMPL_H */

