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


    passive_radar_cc_sptr make_passive_radar_cc( 
                                                  float fs_in,
                                                  float duration,
                                                  unsigned int sources_count,
                                                  unsigned int channels_count,
                                                  unsigned int vector_length
                                                    )
    {
      return passive_radar_cc_sptr (new passive_radar_cc(
                                                         float fs_in,
                                                         float duration,
                                                         unsigned int sources_count,
                                                         unsigned int channels_count,
                                                         unsigned int vector_length
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
                                       unsigned int vector_length
                                        )
      : gr::sync_block("passive_radar",
              gr::io_signature::make(1, -1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0))
    {}

    /*
     * Our virtual destructor.
     */
    passive_radar_cc::~passive_radar_cc()
    {
    }

    int
    passive_radar_cc::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex  * in = (const  gr_complex *) input_items[0];
      

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }


