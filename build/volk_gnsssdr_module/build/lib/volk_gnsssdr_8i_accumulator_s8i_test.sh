#!/bin/sh
export IFS=:
export srcdir="/home/ubuntu/passive_radar/gnss-sdr/src/algorithms/libs/volk_gnsssdr_module/volk_gnsssdr/lib"
export PATH="$1:$PATH"
export LD_LIBRARY_PATH="$*:$LD_LIBRARY_PATH"
 volk_gnsssdr_test_all volk_gnsssdr_8i_accumulator_s8i
