//
//    Copyright (C) 2014 Haruki Hasegawa
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#ifndef CXXPORTHELPER_CXXPORTHELPER_CONFIG_HPP_
#define CXXPORTHELPER_CXXPORTHELPER_CONFIG_HPP_

// include <utility> to detect whether STLPort is used
#include <utility>

#ifdef _STLPORT_VERSION
#define CXXPH_CONFIG_USE_STLPORT 1
#else
#define CXXPH_CONFIG_USE_STLPORT 0
#endif

// runtime MMX instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MMX
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MMX 1
#endif

// runtime SSE instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE 1
#endif

// runtime SSE2 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE2
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE2 1
#endif

// runtime SSE3 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE3
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE3 1
#endif

// runtime SSSE3 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSSE3
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSSE3 1
#endif

// runtime SSE4.1 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_1
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_1 1
#endif

// runtime SSE4.2 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_2
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_2 1
#endif

// runtime SSE4A instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4A
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4A 1
#endif

// runtime AVX instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX 1
#endif

// runtime AVX2 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX2
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX2 1
#endif

// runtime AVX512F instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512F
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512F 1
#endif

// runtime AVX512CD instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512CD
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512CD 1
#endif

// runtime AVX512DQ instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512DQ
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512DQ 1
#endif

// runtime AVX512BW instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512BW
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512BW 1
#endif

// runtime AVX512VL instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512VL
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512VL 1
#endif

// runtime AVX512PF instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512PF
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512PF 1
#endif

// runtime AVX512ER instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512ER
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512ER 1
#endif

// runtime FMA instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_FMA
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_FMA 1
#endif

// runtime MOVBE instruction support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MOVBE
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MOVBE 1
#endif

// runtime POPCNT instruction support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_POPCNT
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_POPCNT 1
#endif

// runtime ARMv7 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_V7
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_V7 1
#endif

// runtime ARM VFPv3 instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_VFP_V3
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_VFP_V3 1
#endif

// runtime ARM NEON instructions support check
#ifndef CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_NEON
#define CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_NEON 1
#endif

#endif // CXXPORTHELPER_CXXPORTHELPER_CONFIG_HPP_
