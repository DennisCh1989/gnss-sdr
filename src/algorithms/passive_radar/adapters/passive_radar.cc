/*!
 * \file gps_l1_ca_dll_pll_tracking.cc
 * \brief Implementation of an adapter of a DLL+PLL tracking loop block
 * for GPS L1 C/A to a TrackingInterface
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *         Javier Arribas, 2011. jarribas(at)cttc.es
 *
 * Code DLL + carrier PLL according to the algorithms described in:
 * K.Borre, D.M.Akos, N.Bertelsen, P.Rinder, and S.H.Jensen,
 * A Software-Defined GPS and Galileo Receiver. A Single-Frequency
 * Approach, Birkhauser, 2007
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
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


#include "passive_radar.h"
#include <glog/logging.h>
#include "GPS_L1_CA.h"
#include "configuration_interface.h"


using google::LogMessage;

PassiveRadar::PassiveRadar(
        ConfigurationInterface* configuration, std::string role,
        unsigned int sources_count, unsigned int channels_count) : role_(role)
{
    DLOG(INFO) << "role " << role;
    //################# CONFIGURATION PARAMETERS ########################
    float fs_in = configuration->property("GNSS-SDR.internal_fs_hz", 2048000);
    float duration  = configuration->property("PASSIVE_RADAR.internal_fs_hz", 1);
    unsigned int vector_length = std::round(fs_in / (GPS_L1_CA_CODE_RATE_HZ / GPS_L1_CA_CODE_LENGTH_CHIPS));

    //################# MAKE PASSIVE RADAR GNURadio object ###################
    passive_radar_ = make_passive_radar_cc(
                                             fs_in,
                                             duration,
                                             sources_count,
                                             channels_count,
                                             vector_length
                                                     );
}


PassiveRadar::~PassiveRadar()
{}

void PassiveRadar::connect(gr::top_block_sptr top_block)
{
    if(top_block) { /* top_block is not null */};
    //nothing to connect, now the tracking uses gr_sync_decimator
}


void PassiveRadar::disconnect(gr::top_block_sptr top_block)
{
    if(top_block) { /* top_block is not null */};
    //nothing to disconnect, now the tracking uses gr_sync_decimator
}


gr::basic_block_sptr PassiveRadar::get_left_block()
{
    return passive_radar_; 
}


gr::basic_block_sptr PassiveRadar::get_right_block()
{
    return passive_radar_;
}

