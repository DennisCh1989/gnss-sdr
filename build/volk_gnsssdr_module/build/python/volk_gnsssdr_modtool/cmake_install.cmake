# Install script for directory: /home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/python/volk_gnsssdr_modtool

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/volk_gnsssdr_modtool" TYPE FILE FILES
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/python/volk_gnsssdr_modtool/__init__.py"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/python/volk_gnsssdr_modtool/cfg.py"
    "/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/python/volk_gnsssdr_modtool/volk_gnsssdr_modtool_generate.py"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/volk_gnsssdr_modtool" TYPE FILE FILES
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/__init__.pyc"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/cfg.pyc"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/volk_gnsssdr_modtool_generate.pyc"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/__init__.pyo"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/cfg.pyo"
    "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/volk_gnsssdr_modtool_generate.pyo"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "volk_gnsssdr")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM RENAME "volk_gnsssdr_modtool" FILES "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/build/python/volk_gnsssdr_modtool/volk_gnsssdr_modtool.exe")
endif()

