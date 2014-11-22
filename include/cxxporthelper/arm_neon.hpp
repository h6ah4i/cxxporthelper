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

#ifndef CXXPORTHELPER_ARM_NEON_HPP_
#define CXXPORTHELPER_ARM_NEON_HPP_

#include <cxxporthelper/compiler.hpp>

#if CXXPH_COMPILER_SUPPORTS_ARM_NEON
#include <arm_neon.h>

#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM)

#define vmulq_lane_f32_compat(a, b, c) vmulq_lane_f32(a, b, c)
#define vmlaq_lane_f32_compat(a, b, c, d) vmlaq_lane_f32(a, b, c, d)

#elif(CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64)

template <int C>
struct vmulq_lane_f32_compat_wrapper {
    static float32x4_t op(float32x4_t a, float32x2_t b) CXXPH_NOEXCEPT
    {
        float32x4_t result;

#if CXXPH_COMPILER_IS_CLANG
        result = a * __builtin_shufflevector(b, b, C, C, C, C);
#else
        asm("fmul %[result].4s, %[a].4s, %[b].2s[%[c]]\n\t"
            : [result] "=w"(result)
            : [a] "w"(a), [b] "w"(b), [c] "i"(C)
            :);
#endif
        return result;
    }
};

template <int C>
struct vmulq_lane_f32_ex_wrapper {
    static float32x4_t op(float32x4_t a, float32x4_t b) CXXPH_NOEXCEPT
    {
        float32x4_t result;

#if CXXPH_COMPILER_IS_CLANG
        result = a * __builtin_shufflevector(b, b, C, C, C, C);
#else
        asm("fmul %[result].4s, %[a].4s, %[b].4s[%[c]]\n\t"
            : [result] "=w"(result)
            : [a] "w"(a), [b] "w"(b), [c] "i"(C)
            :);
#endif

        return result;
    }
};

template <int D>
struct vmlaq_lane_f32_compat_wrapper {
    static float32x4_t op(float32x4_t a, float32x4_t b, float32x2_t c) CXXPH_NOEXCEPT
    {
#if CXXPH_COMPILER_IS_CLANG
        float32x4_t result;

        result = a + b * __builtin_shufflevector(c, c, D, D, D, D);

        return result;
#else
#if 0
        float32x4_t result;

        asm (
            "fmul %[result].4s, %[b].4s, %[c].2s[%[d]]\n\t"
            "fadd %[result].4s, %[result].4s, %[a].4s\n\t"
            : [result]"+w"(result)
            : [a]"w"(a), [b]"w"(b), [c]"w"(c), [d]"i"(D)
            : );

        return result;
#else
        asm("fmla %[result].4s, %[b].4s, %[c].2s[%[d]]\n\t" : [result] "+w"(a) : [b] "w"(b), [c] "w"(c), [d] "i"(D) :);

        return a;
#endif
#endif
    }
};

template <int D>
struct vmlaq_lane_f32_ex_wrapper {
    static float32x4_t op(float32x4_t a, float32x4_t b, float32x4_t c) CXXPH_NOEXCEPT
    {
#if CXXPH_COMPILER_IS_CLANG
        float32x4_t result;

        result = a + b * __builtin_shufflevector(c, c, D, D, D, D);

        return result;
#else
#if 0
        float32x4_t result;

        asm (
            "fmul %[result].4s, %[b].4s, %[c].4s[%[d]]\n\t"
            "fadd %[result].4s, %[result].4s, %[a].4s\n\t"
            : [result]"+w"(result)
            : [a]"w"(a), [b]"w"(b), [c]"w"(c), [d]"i"(D)
            : );

        return result;
#else
        asm("fmla %[result].4s, %[b].4s, %[c].4s[%[d]]\n\t" : [result] "+w"(a) : [b] "w"(b), [c] "w"(c), [d] "i"(D) :);

        return a;
#endif
#endif
    }
};

#define vmulq_lane_f32_compat(a, b, c) vmulq_lane_f32_compat_wrapper<(c)>::op((a), (b))
#define vmulq_lane_f32_ex(a, b, c) vmulq_lane_f32_ex_wrapper<(c)>::op((a), (b))
#define vmlaq_lane_f32_compat(a, b, c, d) vmlaq_lane_f32_compat_wrapper<(d)>::op((a), (b), (c))
#define vmlaq_lane_f32_ex(a, b, c, d) vmlaq_lane_f32_ex_wrapper<(d)>::op((a), (b), (c))

#endif

#endif // CXXPH_COMPILER_SUPPORTS_ARM_NEON

#endif // CXXPORTHELPER_ARM_NEON_HPP_
