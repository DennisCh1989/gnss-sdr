/*!
 * \file unpack_intspir_1bit_samples.h
 *
 * \brief Unpacks SPIR int samples to NSR 1 bit samples
 * \author Fran Fabra fabra (at) ice.csic.es
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is not part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_UNPACK_INTSPIR_1BIT_SAMPLES_H
#define GNSS_SDR_UNPACK_INTSPIR_1BIT_SAMPLES_H

#include <gnuradio/sync_interpolator.h>

class unpack_intspir_1bit_samples;

typedef boost::shared_ptr<unpack_intspir_1bit_samples> unpack_intspir_1bit_samples_sptr;

unpack_intspir_1bit_samples_sptr make_unpack_intspir_1bit_samples();

/*!
 * \brief This class implements conversion between byte packet samples to 2bit samples
 *  1 byte = 4 2bit samples
 */
class unpack_intspir_1bit_samples: public gr::sync_interpolator
{
private:
    friend unpack_intspir_1bit_samples_sptr
    make_unpack_intspir_1bit_samples_sptr();

public:
    unpack_intspir_1bit_samples();
    ~unpack_intspir_1bit_samples();
    int work (int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);
};

#endif
