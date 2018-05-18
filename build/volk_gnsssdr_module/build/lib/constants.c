/* -*- c++ -*- */
/* Copyright (C) 2010-2018 (see AUTHORS file for a list of contributors)
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
 * along with GNSS-SDR. If not, see <https://www.gnu.org/licenses/>.
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <volk_gnsssdr/constants.h>

const char*
volk_gnsssdr_prefix()
{
  const char *prefix = getenv("VOLK_GNSSSDR_PREFIX");
  if (prefix != NULL) return prefix;
  return "/home/ubuntu/passive_radar/gnss-sdr/build/volk_gnsssdr_module/install";
}

const char*
volk_gnsssdr_version()
{
  return "0.0.9.git";
}

const char*
volk_gnsssdr_c_compiler()
{
  return "cc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609 \nCopyright (C) 2015 Free Software Foundation, Inc. \nThis is free software see the source for copying conditions.  There is NO \nwarranty not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";
}

const char*
volk_gnsssdr_compiler_flags()
{
  return "/usr/bin/cc:::  -Wall \n/usr/bin/c++:::   -std=c++11 -Wall -Wextra -Wall \ngeneric:::GNU:::-O3 -DNDEBUG  -Wall  \nsse2_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 \nsse3_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 \nssse3_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -mssse3 \nsse4_a_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -msse4a -mpopcnt \nsse4_1_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 \nsse4_2_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mpopcnt \navx_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mpopcnt -mavx \navx2_64_mmx:::GNU:::-O3 -DNDEBUG  -Wall -m64 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mpopcnt -mavx -mfma -mavx2";
}

const char*
volk_gnsssdr_available_machines()
{
  return "generic;sse2_64_mmx;sse3_64_mmx;ssse3_64_mmx;sse4_a_64_mmx;sse4_1_64_mmx;sse4_2_64_mmx;avx_64_mmx;avx2_64_mmx";
}
