# Install script for directory: /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr_devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/volk_gnsssdr.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr_devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/kernels/volk_gnsssdr" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr_devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/volk_gnsssdr" TYPE FILE FILES
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_prefs.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_complex.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_common.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/saturation_arithmetic.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_avx_intrinsics.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_sse_intrinsics.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_sse3_intrinsics.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_neon_intrinsics.h"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/include/volk_gnsssdr/volk_gnsssdr.h"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/include/volk_gnsssdr/volk_gnsssdr_cpu.h"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/include/volk_gnsssdr/volk_gnsssdr_config_fixed.h"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/include/volk_gnsssdr/volk_gnsssdr_typedefs.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_malloc.h"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/include/volk_gnsssdr/volk_gnsssdr_sine_table.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr_devel")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/volk_gnsssdr" TYPE FILE FILES
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/cmake/Modules/VolkGnsssdrConfig.cmake"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/cmake/Modules/VolkGnsssdrConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/lib/cmake_install.cmake")
  include("/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/apps/cmake_install.cmake")
  include("/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
