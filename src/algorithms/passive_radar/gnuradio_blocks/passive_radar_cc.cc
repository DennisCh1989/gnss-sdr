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
#include <pmt/pmt.h>
#include <gnuradio/tags.h>
#include <volk/volk.h>

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
    }

    /*
     * Our virtual destructor.
     */
    passive_radar_cc::~passive_radar_cc()
    {
    }

    int
    passive_radar_cc::work(int noutput_items __attribute__ ((unused)),
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items __attribute__ ((unused)))
    {
      
      for (unsigned int signal_conditioner_id =0;signal_conditioner_id < d_conditioners_count;signal_conditioner_id++)
	{
	  for (unsigned channel_id = d_sources_count; channel_id < d_channels_count+d_sources_count; channel_id++)
	    {
	      std::vector<gr::tag_t> symbols;
	      get_tags_in_window(
			        symbols,
			        channel_id,
			        0,
			        d_conv_chunk ,
				pmt::mp("reliable symbol")
                                 );

	     for (unsigned int i =0;i < symbols.size();i++)
	       {
	         unsigned int symbol_pos = symbols[i].offset - nitems_read(0);
		 unsigned int channel_index_in_IDs = channel_id - d_conditioners_count;
		 float *cVec =  &((float*) &input_items[d_IDs[channel_index_in_IDs]])[symbol_pos*2];
		 float *aVec =  cVec;
		 float *bVec =  &((float*) &input_items[channel_id])[symbol_pos*2];
		 unsigned int symbol_samples_length = pmt::to_long(symbols[i].value);
		 volk_32f_x2_subtract_32f(cVec,aVec,bVec,symbol_samples_length*sizeof(gr_complex)/sizeof(float));
	       }
	    }
	}

      // Tell runtime system how many output items we produced.
      return d_conv_chunk;
    }


