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
     set(OPT_PASSIVE_RADAR_BLOCKS ${OPT_PASSIVE_RADAR_BLOCKS} passive_radar_cc.cc)
     set(OPT_PASSIVE_RADAR_INCLUDES ${OPT_PASI+SIVE_RADAR_INCLUDES} ${CUDA_INCLUDE_DIRS})
     set(OPT_PASSIVE_RADAR_LIBRARIES ${OPT_PASSIVE_RADAR_LIBRARIES} ${CUDA_LIBRARIES}) 
endif(ENABLE_CUDA)

set(PASSIVE_RADAR_GR_BLOCKS_SOURCES
     passive_radar_cc.cc
     ${OPT_PASSIVE_RADAR_BLOCKS}   
)

include_directories(
     $(CMAKE_CURRENT_SOURCE_DIR)
     ${CMAKE_SOURCE_DIR}/src/core/system_parameters
     ${CMAKE_SOURCE_DIR}/src/core/interfaces
     ${CMAKE_SOURCE_DIR}/src/core/receiver
     ${CMAKE_SOURCE_DIR}/src/algorithms/libs
     ${GLOG_INCLUDE_DIRS}
     ${GFlags_INCLUDE_DIRS}
     ${Boost_INCLUDE_DIRS}
     ${GNURADIO_RUNTIME_INCLUDE_DIRS}
     ${VOLK_GNSSSDR_INCLUDE_DIRS}
     ${OPT_PASSIVE_RADAR_INCLUDES}
)

if(ENABLE_GENERIC_ARCH)
    add_definitions( -DGENERIC_ARCH=1 )
endif(ENABLE_GENERIC_ARCH)

file(GLOB PASSIVE_RADAR_GR_BLOCKS_HEADERS "*.h")
list(SORT PASSIVE_RADAR_GR_BLOCKS_HEADERS)
add_library(passive_radar_gr_blocks ${PASSIVE_RADAR_GR_BLOCKS_SOURCES} ${PASSIVE_RADAR_GR_BLOCKS_HEADERS})
source_group(Headers FILES ${PASSIVE_RADAR_GR_BLOCKS_HEADERS})

target_link_libraries(passive_radar_gr_blocks passive_radar_lib ${GNURADIO_RUNTIME_LIBRARIES} gnss_sp_libs ${Boost_LIBRARIES} ${VOLK_GNSSSDR_LIBRARIES} ${OPT_PASSIVE_RADAR_LIBRARIES})

if(NOT VOLK_GNSSSDR_FOUND)
    add_dependencies(passive_radar_gr_blocks volk_gnsssdr_module)
endif(NOT VOLK_GNSSSDR_FOUND)
