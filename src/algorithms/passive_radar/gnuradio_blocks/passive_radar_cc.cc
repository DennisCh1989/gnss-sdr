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
#include <gnuradio/filter/firdes.h>
#include <thread>
#include <limits> 

    const float DOPPLER_DEFINITION = 0.25;
    const float MAX_TIME_SHIFT     = 0.1;
    const unsigned int MIN_PATHS_REQUIRED = 4;
    const float STRONG_BITS_FREQ = 0.9;
    const float eps = std::numeric_limits<float>::epsilon();
    const double GAIN = 1.0;
    const double END_PASS_BAND = 0.44;
    const double START_STOP_BAND = 0.49; 
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
      d_conv_chunk = static_cast<unsigned int> (duration * fs_in);
      d_IDs = IDs;
      d_run_detector = false;
      d_doppler_range = -5000;
      d_doppler_step = (1/duration)*DOPPLER_DEFINITION;
      d_resampling_doppler_dist =MAX_TIME_SHIFT/(GPS_L1_CA_CODE_RATE_HZ*duration) *GPS_L1_FREQ_HZ;
      d_resampling_step = static_cast<unsigned int> ((d_resampling_doppler_dist+eps)/d_doppler_step);
           
      std::vector<float> taps = gr::filter::firdes::low_pass(
							     GAIN,
							     fs_in*FILTER_SIZE,
							     fs_in*END_PASS_BAND,
							     fs_in*(START_STOP_BAND-END_PASS_BAND),
							     WINDOW
							     );
      
      d_resamp = new gr::filter::kernel::pfb_arb_resampler_ccf(1, taps, FILTER_SIZE);
      float max_chip_rate_err = d_doppler_range/GPS_L1_FREQ_HZ; 
      d_resampled_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]);
      d_freq_shift_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]); 
      unsigned int d_vector_length = static_cast<unsigned int> (fs_in / (GPS_L1_CA_CODE_RATE_HZ / GPS_L1_CA_CODE_LENGTH_CHIPS))*GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*2;
      set_history(d_vector_length);
    }

    /*
     * Our virtual destructor.
     */
    passive_radar_cc::~passive_radar_cc()
    {
    }

    std::vector<unsigned int> reliable_channel;

    int passive_radar_cc::work(int noutput_items __attribute__ ((unused)),
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items __attribute__ ((unused)))
    {

      if (d_run_detector) return d_conv_chunk;
      d_run_detector = true;
      std::thread([this,input_items]
		  {
		    for (unsigned ch =0;ch < d_channels_count;ch++)
		      {
			if (reliable_channel[ch] < GPS_CA_TELEMETRY_SYMBOLS_PER_BIT*GPS_CA_TELEMETRY_RATE_BITS_SECOND) continue;

			gr_complex *in = (gr_complex*) input_items[d_IDs[ch]];
					  
			// here perform direct FFT for input_items[ch + d_conditioners_count]

			unsigned int start_res_pos = 0;
	  
			for (float  doppler = -d_doppler_range;doppler < d_doppler_range;doppler+=d_doppler_step,
			     start_res_pos++) 
			  {

			    if (start_res_pos % d_resampling_step == 0)
			      {
				
				d_resamp -> set_phase(0);
				d_resamp -> set_rate(static_cast<float>(FILTER_SIZE)*(1 - doppler/GPS_L1_FREQ_HZ));
				
				int nitems_read;
				int processed = d_resamp->filter(d_resampled_input.get(), in, d_conv_chunk, nitems_read);

				for (int i = processed;i < d_conv_chunk;i++)
				  {
				    d_resampled_input.get()[i] =0;
				  }
			      }

			    memcpy(d_freq_shift_input.get(), d_resampled_input.get(), sizeof(gr_complex)*d_conv_chunk);
			    // here correct  d_freq_shift_doppler by doppler shift
			    // here perform  direct FFT for d_freq_shift_doppler
			    // here perform  element-wise production d_freq_shift_doppler with FFT(input_items[ch])
			    // here perform  Inverse FFT
			    // here get magnitudes
			  }
		      }
        
		    d_run_detector = false;
		  });
      // Tell runtime system how many output items we produced.
      return d_conv_chunk;
    }


