# Copyright (C) 2012-2015  (see AUTHORS file for a list of contributors)
#
# This file is part of GNSS-SDR.
#
# GNSS-SDR is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GNSS-SDR is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
#

if(ENABLE_CUDA)
     set(OPT_PASSIVE_RADAR_ADAPTERS ${OPT_PASSIVE_RADAR_ADAPTERS} passive_radar.cc)
     set(OPT_PASSIVE_RADAR_INCLUDE_DIRS ${OPT_PASSIVE_RADAR_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})
endif(ENABLE_CUDA)

set(TRACKING_ADAPTER_SOURCES 
     passive_radar.cc
     ${OPT_PASSIVE_RADAR_ADAPTERS}
)
 
include_directories(
     $(CMAKE_CURRENT_SOURCE_DIR)
     ${CMAKE_SOURCE_DIR}/src/core/system_parameters
     ${CMAKE_SOURCE_DIR}/src/core/interfaces
     ${CMAKE_SOURCE_DIR}/src/core/receiver
     ${CMAKE_SOURCE_DIR}/src/algorithms/passive_radar/gnuradio_blocks
     ${CMAKE_SOURCE_DIR}/src/algorithms/passive_radar/libs
     ${CMAKE_SOURCE_DIR}/src/algorithms/libs
     ${GLOG_INCLUDE_DIRS}
     ${GFlags_INCLUDE_DIRS}
     ${GNURADIO_RUNTIME_INCLUDE_DIRS}
     ${VOLK_GNSSSDR_INCLUDE_DIRS}
     ${OPT_PASSIVE_RADAR_INCLUDE_DIRS}
)

file(GLOB PASSIVE_RADAR_ADAPTER_HEADERS "*.h")
list(SORT PASSIVE_RADAR_ADAPTER_HEADERS)
add_library(passive_radar_adapters ${PASSIVE_RADAR_ADAPTER_SOURCES} ${PASSIVE_RADAR_ADAPTER_HEADERS})
source_group(Headers FILES ${PASSIVE_RADAR_ADAPTER_HEADERS})
target_link_libraries(passive_radar_adapters passive_radar_gr_blocks gnss_sp_libs)
