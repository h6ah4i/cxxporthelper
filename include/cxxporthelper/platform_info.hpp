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

#ifndef CXXPORTHELPER_PLATFORM_INFO_HPP_
#define CXXPORTHELPER_PLATFORM_INFO_HPP_

#include <bitset>

#include <cxxporthelper/impl/cxxporthelper_config.hpp>
#include <cxxporthelper/compiler.hpp>

namespace cxxporthelper {
namespace platform_info {

/**
 * Platform info provider
 */
class platform_info_provider {
public:
    /**
     * Feature flag index
     */
    enum feature_index_t {
        // for i386/x86_64 processors
        FEATURE_INDEX_X86_MMX,
        FEATURE_INDEX_X86_SSE,
        FEATURE_INDEX_X86_SSE2,
        FEATURE_INDEX_X86_SSE3,
        FEATURE_INDEX_X86_SSSE3,
        FEATURE_INDEX_X86_SSE4_1,
        FEATURE_INDEX_X86_SSE4_2,
        FEATURE_INDEX_X86_SSE4A,
        FEATURE_INDEX_X86_AVX,
        FEATURE_INDEX_X86_AVX2,
        FEATURE_INDEX_X86_AVX512F,  // AVX-512 Foundation
        FEATURE_INDEX_X86_AVX512CD, // AVX-512 Conflict Detection Instructions
        FEATURE_INDEX_X86_AVX512DQ, // AVX-512 Doubleword and Quadword Instructions
        FEATURE_INDEX_X86_AVX512BW, // AVX-512 Byte and Word Instructions
        FEATURE_INDEX_X86_AVX512VL, // AVX-512 Vector Length Extensions
        FEATURE_INDEX_X86_AVX512PF, // AVX-512 Prefetch Instructions
        FEATURE_INDEX_X86_AVX512ER, // AVX-512 Exponential and Reciprocal Instructions
        FEATURE_INDEX_X86_FMA,
        FEATURE_INDEX_X86_MOVBE,
        FEATURE_INDEX_X86_POPCNT,

        // for ARM (AArch32, AArch64) processors
        FEATURE_INDEX_ARM_V7,
        FEATURE_INDEX_ARM_VFP_V3,
        FEATURE_INDEX_ARM_NEON,

        // num indices
        NUM_FEATURE_INDICES,
    };

    /**
     * Constructor.
     */
    platform_info_provider();

    /**
     * Destructor.
     */
    ~platform_info_provider();

    /**
     * Check whether the specified feature is available.
     *
     * @param index [in] feature index
     */
    bool check_feature(feature_index_t index) const CXXPH_NOEXCEPT
    {
        if (index < 0 || index >= NUM_FEATURE_INDICES)
            return false;
        return feature_flags_[index];
    }

private:
    /// @cond INTERNAL_FIELD
    std::bitset<NUM_FEATURE_INDICES> feature_flags_;
    /// @endcond
};

const platform_info_provider &get_platform_info_provider_instance() CXXPH_NOEXCEPT;

inline bool check_feature(platform_info_provider::feature_index_t index)
{
    return get_platform_info_provider_instance().check_feature(index);
}

/**
 * Check whether MMX (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_MMX)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MMX
inline bool support_mmx() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_MMX); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_mmx() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_mmx() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE
inline bool support_sse() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE2 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE2)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE2
inline bool support_sse2() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE2); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse2() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse2() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE3 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE3)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE3
inline bool support_sse3() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE3); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse3() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse3() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSSE3 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSSE3)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSSE3
inline bool support_ssse3() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSSE3); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_ssse3() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_ssse3() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE4.1 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE4_1)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_1
inline bool support_sse4_1() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE4_1); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4_1() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4_1() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE4.2 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE4_2)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4_2
inline bool support_sse4_2() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE4_2); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4_2() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4_2() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether SSE4A (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_SSE4A)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_SSE4A
inline bool support_sse4a() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_SSE4A); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4a() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_sse4a() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX
inline bool support_avx() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX2 (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX2)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX2
inline bool support_avx2() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX2); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx2() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx2() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512F (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512F)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512F
inline bool support_avx512f() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512F);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512f() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512f() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512CD (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512CD)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512CD
inline bool support_avx512cd() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512CD);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512cd() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512cd() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512DQ (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512DQ)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512DQ
inline bool support_avx512dq() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512DQ);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512dq() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512dq() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512BW (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512BW)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512BW
inline bool support_avx512bw() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512BW);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512bw() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512bw() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512VL (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512VL)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512VL
inline bool support_avx512vl() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512VL);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512vl() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512vl() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512ER (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512ER)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512ER
inline bool support_avx512er() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512ER);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512er() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512er() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether AVX512PF (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_AVX512PF)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_AVX512PF
inline bool support_avx512pf() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_X86_AVX512PF);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512pf() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_avx512pf() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether FMA (x86) instructions are available
 */
#if defined(CXXPH_COMPILER_SUPPORTS_X86_FMA)
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_FMA
inline bool support_fma() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_FMA); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_fma() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_fma() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether MOVBE (x86) instruction is available
 */
#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64))
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_MOVBE
inline bool support_movbe() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_MOVBE); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_movbe() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_movbe() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether POPCNT (x86) instruction is available
 */
#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64))
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_X86_POPCNT
inline bool support_popcnt() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_X86_POPCNT); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_popcnt() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_popcnt() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether ARMv7 (ARM) instructions are available
 */
#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64))
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_V7
inline bool support_armv7() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_ARM_V7); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_armv7() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_armv7() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether ARM VFPv3 (ARM) instructions are available
 */
#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64))
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_VFP_V3
inline bool support_arm_vfpv3() CXXPH_NOEXCEPT
{
    return check_feature(platform_info_provider::FEATURE_INDEX_ARM_VFP_V3);
}
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_arm_vfpv3() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_arm_vfpv3() CXXPH_NOEXCEPT { return false; }
#endif

/**
 * Check whether ARM NEON (ARM) instructions are available
 */
#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64))
#if CXXPH_CONFIG_RUNTIME_FEATURE_CHECK_ARM_NEON
inline bool support_arm_neon() CXXPH_NOEXCEPT { return check_feature(platform_info_provider::FEATURE_INDEX_ARM_NEON); }
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_arm_neon() CXXPH_NOEXCEPT { return true; }
#endif
#else
inline CXXPH_OPTIONAL_CONSTEXPR bool support_arm_neon() CXXPH_NOEXCEPT { return false; }
#endif

} // namespace platform_info
} // namespace cxxporthelper

#endif /* CXXPORTHELPER_PLATFORM_INFO_HPP_ */
