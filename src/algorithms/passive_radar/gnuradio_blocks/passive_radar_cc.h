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

#ifndef INCLUDED_PASSIVE_RADAR_PASSIVE_RADAR_IMPL_H
#define INCLUDED_PASSIVE_RADAR_PASSIVE_RADAR_IMPL_H

#include <passive_radar/passive_radar.h>

typedef boost::shared_ptr<passive_radar_cc>
               passive_radar_cc_sptr;

passive_radar_cc_sptr
make_passive_radar_cc(
                        float fs_in,
                        float duration,
                        unsigned int sources_count,
                        unsigned int channles_count,
                        unsigned int vector_length
                       );

    class passive_radar_cc : public passive_radar
    {
     private:
      friend passive_radar_cc_sptr make_passive_radar_cc(
                                                          float fs_in,
                                                          float duration,
                                                          unsigned int sources_count,
                                                          unsigned int channles_count,
                                                          unsigned int vector_length
                                                           );

     public:
      passive_radar_cc();
      ~passive_radar_cc();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };


#endif /* INCLUDED_PASSIVE_RADAR_PASSIVE_RADAR_IMPL_H */

