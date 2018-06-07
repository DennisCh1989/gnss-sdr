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
#include <thread>

    const float DOPPLER_DEFINITION = 0.25;
    const float MAX_TIME_SHIFT     = 0.1;
    const unsigned int MIN_PATHS_REQUIRED = 4; 

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
      d_threshold =static_cast<unsigned int> (duration*GPS_CA_TELEMETRY_RATE_BITS_SECOND*GPS_CA_TELEMETRY_SYMBOLS_PER_BIT);
      d_resampling_doppler_dist =MAX_TIME_SHIFT/(GPS_L1_CA_CODE_RATE_HZ*duration) *GPS_L1_FREQ_HZ;
      std::vector<float> taps;
      d_resamp = new gr::filter::kernel::pfb_arb_resampler_ccf(1, taps, 1);
      float max_chip_rate_err = d_doppler_range/GPS_L1_FREQ_HZ; 
      d_resampled_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]);
      d_freq_shift_input = std::shared_ptr<gr_complex>(new gr_complex[static_cast<unsigned int>(d_conv_chunk*(1+max_chip_rate_err*2))]); 
      d_reliable_channel_flags.resize(d_channels_count);
    }

    /*
     * Our virtual destructor.
     */
    passive_radar_cc::~passive_radar_cc()
    {
    }

    void passive_radar_cc::detector(gr_vector_const_void_star input_items)
    {
      for (unsigned int  conditioner_id =0; conditioner_id < d_conditioners_count; conditioner_id++)
	{

          gr_complex *in = (gr_complex*) input_items[conditioner_id];

	  for (unsigned ch =0;ch < d_channels_count;ch++)
	    {
	      if (conditioner_id == d_IDs[ch]  and d_reliable_channel_flags[ch])
		{
		  float resampling_last_doppler = 0;
		  
		  // here perform direct FFT for input_items[ch + d_conditioners_count]
		  
		  for (float doppler = -d_doppler_range;doppler < d_doppler_range;doppler+=d_doppler_step) 
		    {

		      if (doppler -resampling_last_doppler >d_resampling_doppler_dist or doppler == - d_doppler_range)
			{
			  resampling_last_doppler = doppler;
			  
			  float chip_rate_err =doppler / GPS_L1_FREQ_HZ;

			  d_resamp -> set_phase(0);
			  d_resamp -> set_rate(1+chip_rate_err);
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
	    }
	}
      
      d_run_detector = false;
    }


    int
    passive_radar_cc::work(int noutput_items __attribute__ ((unused)),
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items __attribute__ ((unused)))
    {

      if (d_run_detector == false)
	{
	   d_run_detector = true;

	   unsigned int reliable_channels =0;

	   for (unsigned channel_id = 0; channel_id < d_channels_count; channel_id++)
	     {
	       std::vector<gr::tag_t> symbols;

               d_reliable_channel_flags[channel_id] = false;

	       get_tags_in_window(
				  symbols,
				  channel_id+d_conditioners_count,
				  0,
				  d_conv_chunk ,
				  pmt::mp("reliable symbol")
				  );
	      
	       if (symbols.size()-1 >  d_threshold)
		 {
                   d_reliable_channel_flags[channel_id] = true;
		   reliable_channels++;
		   
		   for (unsigned int i =0;i < symbols.size();i++)
		     {
		       unsigned int symbol_pos = symbols[i].offset - nitems_read(0);
		       unsigned int conditioner_id_for_chan = d_IDs[channel_id];
		       float *cVec =  &((float*) &input_items[conditioner_id_for_chan])[symbol_pos*2];
		       float *aVec =  cVec; 
		       float *bVec =  &((float*) &input_items[channel_id+d_conditioners_count])[symbol_pos*2];
		       unsigned int symbol_samples_length = pmt::to_long(symbols[i].value);
		       volk_32f_x2_subtract_32f(cVec,aVec,bVec,symbol_samples_length*sizeof(gr_complex)/sizeof(float));
		     }
		 }
	     }

	   if (reliable_channels >= MIN_PATHS_REQUIRED)
	     {
	       std::thread(&passive_radar_cc::detector,this,input_items);
	     }
	   else
	     {
	       d_run_detector = false;
	     }
	}
      
      // Tell runtime system how many output items we produced.
      return d_conv_chunk;
    }


