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

#ifndef CXXPORTHELPER_X86_INTRINSICS_HPP_
#define CXXPORTHELPER_X86_INTRINSICS_HPP_

#include <cxxporthelper/compiler.hpp>

#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)

//
// include header files
//
#if CXXPH_COMPILER_IS_MSVC
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#if CXXPH_COMPILER_IS_MSVC
// fix undefined _mm_load_pd1
#if !defined(_mm_load_pd1)
#define _mm_load_pd1(x) _mm_load1_pd(x)
#endif
#endif

namespace cxxporthelper {
namespace x86intrinsics {
//
// load & store operators
//
#if CXXPH_COMPILER_SUPPORTS_X86_SSE
struct sse_m128_load_aligned {
    static __m128 load(const float *mem_addr) { return _mm_load_ps(mem_addr); }
};

struct sse_m128_load_unaligned {
    static __m128 load(const float *mem_addr) { return _mm_loadu_ps(mem_addr); }
};

struct sse_m128_store_aligned {
    static void store(float *mem_addr, const __m128 &a) { _mm_store_ps(mem_addr, a); }
};

struct sse_m128_store_unaligned {
    static void store(float *mem_addr, const __m128 &a) { _mm_storeu_ps(mem_addr, a); }
};
#endif

#if CXXPH_COMPILER_SUPPORTS_X86_SSE2
struct sse2_m128d_load_aligned {
    static __m128d load(const double *mem_addr) { return _mm_load_pd(mem_addr); }
};

struct sse2_m128d_load_unaligned {
    static __m128d load(const double *mem_addr) { return _mm_loadu_pd(mem_addr); }
};

struct sse2_m128d_store_aligned {
    static void store(double *mem_addr, const __m128d &a) { _mm_store_pd(mem_addr, a); }
};

struct sse2_m128d_store_unaligned {
    static void store(double *mem_addr, const __m128d &a) { _mm_storeu_pd(mem_addr, a); }
};

struct sse2_m128i_load_aligned {
    static __m128i load(const __m128i *mem_addr) { return _mm_load_si128(mem_addr); }
};

struct sse2_m128i_load_unaligned {
    static __m128i load(const __m128i *mem_addr) { return _mm_loadu_si128(mem_addr); }
};

struct sse2_m128i_store_aligned {
    static void store(__m128i *mem_addr, const __m128i &a) { _mm_store_si128(mem_addr, a); }
};

struct sse2_m128i_store_unaligned {
    static void store(__m128i *mem_addr, const __m128i &a) { _mm_storeu_si128(mem_addr, a); }
};
#endif

#if CXXPH_COMPILER_SUPPORTS_X86_SSE3
struct sse3_m128i_load_unaligned {
    static __m128i load(const __m128i *mem_addr) { return _mm_lddqu_si128(mem_addr); }
};
#endif

} // namespace x86intrinsics
} // namespace cxxporthelper

#endif // (CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)

#endif // CXXPORTHELPER_X86_INTRINSICS_HPP_
