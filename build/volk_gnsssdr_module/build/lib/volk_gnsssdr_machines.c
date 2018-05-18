
        
/* this file was generated by volk_gnsssdr template utils, do not edit! */
        
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

#include <volk_gnsssdr/volk_gnsssdr_common.h>
#include <volk_gnsssdr/volk_gnsssdr_typedefs.h>
#include "volk_gnsssdr_machines.h"

// clang-format off
struct volk_gnsssdr_machine *volk_gnsssdr_machines[] = {
#ifdef LV_MACHINE_GENERIC_ORC
&volk_gnsssdr_machine_generic_orc,
#endif
#ifdef LV_MACHINE_GENERIC
&volk_gnsssdr_machine_generic,
#endif
#ifdef LV_MACHINE_NEON_ORC
&volk_gnsssdr_machine_neon_orc,
#endif
#ifdef LV_MACHINE_NEON
&volk_gnsssdr_machine_neon,
#endif
#ifdef LV_MACHINE_NEONV7_SOFTFP_ORC
&volk_gnsssdr_machine_neonv7_softfp_orc,
#endif
#ifdef LV_MACHINE_NEONV7_SOFTFP
&volk_gnsssdr_machine_neonv7_softfp,
#endif
#ifdef LV_MACHINE_NEONV7_HARDFP_ORC
&volk_gnsssdr_machine_neonv7_hardfp_orc,
#endif
#ifdef LV_MACHINE_NEONV7_HARDFP
&volk_gnsssdr_machine_neonv7_hardfp,
#endif
#ifdef LV_MACHINE_NEONV8
&volk_gnsssdr_machine_neonv8,
#endif
#ifdef LV_MACHINE_SSE2_32_MMX_ORC
&volk_gnsssdr_machine_sse2_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE2_32_MMX
&volk_gnsssdr_machine_sse2_32_mmx,
#endif
#ifdef LV_MACHINE_SSE2_32_ORC
&volk_gnsssdr_machine_sse2_32_orc,
#endif
#ifdef LV_MACHINE_SSE2_32
&volk_gnsssdr_machine_sse2_32,
#endif
#ifdef LV_MACHINE_SSE2_64_MMX_ORC
&volk_gnsssdr_machine_sse2_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE2_64_MMX
&volk_gnsssdr_machine_sse2_64_mmx,
#endif
#ifdef LV_MACHINE_SSE2_64_ORC
&volk_gnsssdr_machine_sse2_64_orc,
#endif
#ifdef LV_MACHINE_SSE2_64
&volk_gnsssdr_machine_sse2_64,
#endif
#ifdef LV_MACHINE_SSE2_MMX_ORC
&volk_gnsssdr_machine_sse2_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE2_MMX
&volk_gnsssdr_machine_sse2_mmx,
#endif
#ifdef LV_MACHINE_SSE2_ORC
&volk_gnsssdr_machine_sse2_orc,
#endif
#ifdef LV_MACHINE_SSE2
&volk_gnsssdr_machine_sse2,
#endif
#ifdef LV_MACHINE_SSE3_32_MMX_ORC
&volk_gnsssdr_machine_sse3_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE3_32_MMX
&volk_gnsssdr_machine_sse3_32_mmx,
#endif
#ifdef LV_MACHINE_SSE3_32_ORC
&volk_gnsssdr_machine_sse3_32_orc,
#endif
#ifdef LV_MACHINE_SSE3_32
&volk_gnsssdr_machine_sse3_32,
#endif
#ifdef LV_MACHINE_SSE3_64_MMX_ORC
&volk_gnsssdr_machine_sse3_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE3_64_MMX
&volk_gnsssdr_machine_sse3_64_mmx,
#endif
#ifdef LV_MACHINE_SSE3_64_ORC
&volk_gnsssdr_machine_sse3_64_orc,
#endif
#ifdef LV_MACHINE_SSE3_64
&volk_gnsssdr_machine_sse3_64,
#endif
#ifdef LV_MACHINE_SSE3_MMX_ORC
&volk_gnsssdr_machine_sse3_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE3_MMX
&volk_gnsssdr_machine_sse3_mmx,
#endif
#ifdef LV_MACHINE_SSE3_ORC
&volk_gnsssdr_machine_sse3_orc,
#endif
#ifdef LV_MACHINE_SSE3
&volk_gnsssdr_machine_sse3,
#endif
#ifdef LV_MACHINE_SSSE3_32_MMX_ORC
&volk_gnsssdr_machine_ssse3_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSSE3_32_MMX
&volk_gnsssdr_machine_ssse3_32_mmx,
#endif
#ifdef LV_MACHINE_SSSE3_32_ORC
&volk_gnsssdr_machine_ssse3_32_orc,
#endif
#ifdef LV_MACHINE_SSSE3_32
&volk_gnsssdr_machine_ssse3_32,
#endif
#ifdef LV_MACHINE_SSSE3_64_MMX_ORC
&volk_gnsssdr_machine_ssse3_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSSE3_64_MMX
&volk_gnsssdr_machine_ssse3_64_mmx,
#endif
#ifdef LV_MACHINE_SSSE3_64_ORC
&volk_gnsssdr_machine_ssse3_64_orc,
#endif
#ifdef LV_MACHINE_SSSE3_64
&volk_gnsssdr_machine_ssse3_64,
#endif
#ifdef LV_MACHINE_SSSE3_MMX_ORC
&volk_gnsssdr_machine_ssse3_mmx_orc,
#endif
#ifdef LV_MACHINE_SSSE3_MMX
&volk_gnsssdr_machine_ssse3_mmx,
#endif
#ifdef LV_MACHINE_SSSE3_ORC
&volk_gnsssdr_machine_ssse3_orc,
#endif
#ifdef LV_MACHINE_SSSE3
&volk_gnsssdr_machine_ssse3,
#endif
#ifdef LV_MACHINE_SSE4_A_32_MMX_ORC
&volk_gnsssdr_machine_sse4_a_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_A_32_MMX
&volk_gnsssdr_machine_sse4_a_32_mmx,
#endif
#ifdef LV_MACHINE_SSE4_A_32_ORC
&volk_gnsssdr_machine_sse4_a_32_orc,
#endif
#ifdef LV_MACHINE_SSE4_A_32
&volk_gnsssdr_machine_sse4_a_32,
#endif
#ifdef LV_MACHINE_SSE4_A_64_MMX_ORC
&volk_gnsssdr_machine_sse4_a_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_A_64_MMX
&volk_gnsssdr_machine_sse4_a_64_mmx,
#endif
#ifdef LV_MACHINE_SSE4_A_64_ORC
&volk_gnsssdr_machine_sse4_a_64_orc,
#endif
#ifdef LV_MACHINE_SSE4_A_64
&volk_gnsssdr_machine_sse4_a_64,
#endif
#ifdef LV_MACHINE_SSE4_A_MMX_ORC
&volk_gnsssdr_machine_sse4_a_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_A_MMX
&volk_gnsssdr_machine_sse4_a_mmx,
#endif
#ifdef LV_MACHINE_SSE4_A_ORC
&volk_gnsssdr_machine_sse4_a_orc,
#endif
#ifdef LV_MACHINE_SSE4_A
&volk_gnsssdr_machine_sse4_a,
#endif
#ifdef LV_MACHINE_SSE4_1_32_MMX_ORC
&volk_gnsssdr_machine_sse4_1_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_1_32_MMX
&volk_gnsssdr_machine_sse4_1_32_mmx,
#endif
#ifdef LV_MACHINE_SSE4_1_32_ORC
&volk_gnsssdr_machine_sse4_1_32_orc,
#endif
#ifdef LV_MACHINE_SSE4_1_32
&volk_gnsssdr_machine_sse4_1_32,
#endif
#ifdef LV_MACHINE_SSE4_1_64_MMX_ORC
&volk_gnsssdr_machine_sse4_1_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_1_64_MMX
&volk_gnsssdr_machine_sse4_1_64_mmx,
#endif
#ifdef LV_MACHINE_SSE4_1_64_ORC
&volk_gnsssdr_machine_sse4_1_64_orc,
#endif
#ifdef LV_MACHINE_SSE4_1_64
&volk_gnsssdr_machine_sse4_1_64,
#endif
#ifdef LV_MACHINE_SSE4_1_MMX_ORC
&volk_gnsssdr_machine_sse4_1_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_1_MMX
&volk_gnsssdr_machine_sse4_1_mmx,
#endif
#ifdef LV_MACHINE_SSE4_1_ORC
&volk_gnsssdr_machine_sse4_1_orc,
#endif
#ifdef LV_MACHINE_SSE4_1
&volk_gnsssdr_machine_sse4_1,
#endif
#ifdef LV_MACHINE_SSE4_2_32_MMX_ORC
&volk_gnsssdr_machine_sse4_2_32_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_2_32_MMX
&volk_gnsssdr_machine_sse4_2_32_mmx,
#endif
#ifdef LV_MACHINE_SSE4_2_32_ORC
&volk_gnsssdr_machine_sse4_2_32_orc,
#endif
#ifdef LV_MACHINE_SSE4_2_32
&volk_gnsssdr_machine_sse4_2_32,
#endif
#ifdef LV_MACHINE_SSE4_2_64_MMX_ORC
&volk_gnsssdr_machine_sse4_2_64_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_2_64_MMX
&volk_gnsssdr_machine_sse4_2_64_mmx,
#endif
#ifdef LV_MACHINE_SSE4_2_64_ORC
&volk_gnsssdr_machine_sse4_2_64_orc,
#endif
#ifdef LV_MACHINE_SSE4_2_64
&volk_gnsssdr_machine_sse4_2_64,
#endif
#ifdef LV_MACHINE_SSE4_2_MMX_ORC
&volk_gnsssdr_machine_sse4_2_mmx_orc,
#endif
#ifdef LV_MACHINE_SSE4_2_MMX
&volk_gnsssdr_machine_sse4_2_mmx,
#endif
#ifdef LV_MACHINE_SSE4_2_ORC
&volk_gnsssdr_machine_sse4_2_orc,
#endif
#ifdef LV_MACHINE_SSE4_2
&volk_gnsssdr_machine_sse4_2,
#endif
#ifdef LV_MACHINE_AVX_32_MMX_ORC
&volk_gnsssdr_machine_avx_32_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX_32_MMX
&volk_gnsssdr_machine_avx_32_mmx,
#endif
#ifdef LV_MACHINE_AVX_32_ORC
&volk_gnsssdr_machine_avx_32_orc,
#endif
#ifdef LV_MACHINE_AVX_32
&volk_gnsssdr_machine_avx_32,
#endif
#ifdef LV_MACHINE_AVX_64_MMX_ORC
&volk_gnsssdr_machine_avx_64_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX_64_MMX
&volk_gnsssdr_machine_avx_64_mmx,
#endif
#ifdef LV_MACHINE_AVX_64_ORC
&volk_gnsssdr_machine_avx_64_orc,
#endif
#ifdef LV_MACHINE_AVX_64
&volk_gnsssdr_machine_avx_64,
#endif
#ifdef LV_MACHINE_AVX_MMX_ORC
&volk_gnsssdr_machine_avx_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX_MMX
&volk_gnsssdr_machine_avx_mmx,
#endif
#ifdef LV_MACHINE_AVX_ORC
&volk_gnsssdr_machine_avx_orc,
#endif
#ifdef LV_MACHINE_AVX
&volk_gnsssdr_machine_avx,
#endif
#ifdef LV_MACHINE_AVX2_32_MMX_ORC
&volk_gnsssdr_machine_avx2_32_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX2_32_MMX
&volk_gnsssdr_machine_avx2_32_mmx,
#endif
#ifdef LV_MACHINE_AVX2_32_ORC
&volk_gnsssdr_machine_avx2_32_orc,
#endif
#ifdef LV_MACHINE_AVX2_32
&volk_gnsssdr_machine_avx2_32,
#endif
#ifdef LV_MACHINE_AVX2_64_MMX_ORC
&volk_gnsssdr_machine_avx2_64_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX2_64_MMX
&volk_gnsssdr_machine_avx2_64_mmx,
#endif
#ifdef LV_MACHINE_AVX2_64_ORC
&volk_gnsssdr_machine_avx2_64_orc,
#endif
#ifdef LV_MACHINE_AVX2_64
&volk_gnsssdr_machine_avx2_64,
#endif
#ifdef LV_MACHINE_AVX2_MMX_ORC
&volk_gnsssdr_machine_avx2_mmx_orc,
#endif
#ifdef LV_MACHINE_AVX2_MMX
&volk_gnsssdr_machine_avx2_mmx,
#endif
#ifdef LV_MACHINE_AVX2_ORC
&volk_gnsssdr_machine_avx2_orc,
#endif
#ifdef LV_MACHINE_AVX2
&volk_gnsssdr_machine_avx2,
#endif
};
// clang-format on
unsigned int n_volk_gnsssdr_machines = sizeof(volk_gnsssdr_machines) / sizeof(*volk_gnsssdr_machines);
