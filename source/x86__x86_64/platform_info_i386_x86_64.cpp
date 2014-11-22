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

#include <cxxporthelper/compiler.hpp>

#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)

#include <cstring>

#include <cxxporthelper/cstdint>
#include <cxxporthelper/platform_info.hpp>
#include <cxxporthelper/x86_intrinsics.hpp>

// #define CPUID_DEBUG
#ifdef CPUID_DEBUG
#include <cstdio>
#endif

#if !(CXXPH_COMPILER_IS_MSVC)
#include <cpuid.h>
#endif

namespace cxxporthelper {
namespace platform_info {

struct cpuid_info {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    cpuid_info() : eax(0), ebx(0), ecx(0), edx(0) {}
};

#if CXXPH_COMPILER_IS_MSVC
static inline void cpuid(uint32_t in_eax, uint32_t in_ecx, cpuid_info *info)
{
    int tmp_info[4] = { 0 };
    ::__cpuidex(tmp_info, static_cast<int>(in_eax), static_cast<int>(in_ecx));
    info->eax = static_cast<uint32_t>(tmp_info[0]);
    info->ebx = static_cast<uint32_t>(tmp_info[1]);
    info->ecx = static_cast<uint32_t>(tmp_info[2]);
    info->edx = static_cast<uint32_t>(tmp_info[3]);
}
#else
static inline void cpuid(uint32_t in_eax, uint32_t in_ecx, cpuid_info *info)
{
    ::__get_cpuid(in_eax, &(info->eax), &(info->ebx), &(info->ecx), &(info->edx));
}
#endif

void i386_x86_64_collect_platform_info(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features)
{
    typedef platform_info_provider::feature_index_t flags;

    uint32_t num_ids = 0;
    uint32_t num_ex_ids = 0;
#ifdef CPUID_DEBUG
    union {
        uint32_t u32[3];
        char str[13];
    } vendor_id = { 0 };
    union {
        uint32_t u32[12];
        char str[49];
    } processor_brand = { 0 };
#endif

    // get count of supported cpuid params, vendor id (eax = 0)
    {
        cpuid_info info;
        cpuid(0, 0, &info);

        num_ids = (info.eax + 1ul);

#ifdef CPUID_DEBUG
        vendor_id.u32[0] = info.ebx;
        vendor_id.u32[1] = info.edx;
        vendor_id.u32[2] = info.ecx;
        vendor_id.str[12] = '\0';
#endif
    }

    if (num_ids == 0) {
        return;
    }

    // get processor info and feature bits (eax = 1)
    // ref.) http://en.wikipedia.org/wiki/CPUID
    {
        cpuid_info info;
        cpuid(1, 0, &info);

        const std::bitset<32> ecx(info.ecx);
        const std::bitset<32> edx(info.edx);

        features.set(flags::FEATURE_INDEX_X86_MMX, edx[23]);
        features.set(flags::FEATURE_INDEX_X86_SSE, edx[25]);
        features.set(flags::FEATURE_INDEX_X86_SSE2, edx[26]);
        features.set(flags::FEATURE_INDEX_X86_SSE3, ecx[0]);
        features.set(flags::FEATURE_INDEX_X86_SSSE3, ecx[9]);
        features.set(flags::FEATURE_INDEX_X86_SSE4_1, ecx[19]);
        features.set(flags::FEATURE_INDEX_X86_SSE4_2, ecx[20]);
        features.set(flags::FEATURE_INDEX_X86_AVX, ecx[28]);
        features.set(flags::FEATURE_INDEX_X86_FMA, ecx[12]);
        features.set(flags::FEATURE_INDEX_X86_MOVBE, ecx[22]);
        features.set(flags::FEATURE_INDEX_X86_POPCNT, ecx[23]);
    }

    // get extended features (eax = 7, ecx = 0)
    if (num_ids >= 8) {
        cpuid_info info;
        cpuid(7, 0, &info);

        const std::bitset<32> ebx(info.ebx);

        features.set(flags::FEATURE_INDEX_X86_AVX2, ebx[5]);
        features.set(flags::FEATURE_INDEX_X86_AVX512F, ebx[16]);
        features.set(flags::FEATURE_INDEX_X86_AVX512DQ, ebx[17]);
        features.set(flags::FEATURE_INDEX_X86_AVX512PF, ebx[26]);
        features.set(flags::FEATURE_INDEX_X86_AVX512ER, ebx[27]);
        features.set(flags::FEATURE_INDEX_X86_AVX512CD, ebx[28]);
        features.set(flags::FEATURE_INDEX_X86_AVX512BW, ebx[30]);
        features.set(flags::FEATURE_INDEX_X86_AVX512VL, ebx[31]);
    }

    // get count of supported extended cpuid params (eax = 0x80000000ul)
    {
        cpuid_info info;
        cpuid(0x80000000ul, 0, &info);

        num_ex_ids = (info.eax >= 0x80000000ul) ? (info.eax - 0x80000000ul + 1ul) : 0;
    }

    if (num_ex_ids >= 1) {
        cpuid_info info;
        cpuid(0x80000001ul, 0, &info);

        const std::bitset<32> ecx(info.ecx);

        features.set(flags::FEATURE_INDEX_X86_SSE4A, ecx[6]);
    }

#ifdef CPUID_DEBUG
    // get processor brand string (eax = 0x80000002, 0x80000003, 0x80000004)
    if (num_ex_ids >= 5) {
        for (uint32_t i = 0; i < 3; ++i) {
            cpuid_info info;
            cpuid(0x80000002ul + i, 0, &info);

            processor_brand.u32[4 * i + 0] = info.eax;
            processor_brand.u32[4 * i + 1] = info.ebx;
            processor_brand.u32[4 * i + 2] = info.ecx;
            processor_brand.u32[4 * i + 3] = info.edx;
        }
        processor_brand.str[48] = '\0';
    }
#endif

#ifdef CPUID_DEBUG
    printf("vendor_id = %s\n", vendor_id.str);
    printf("processor_brand = %s\n", processor_brand.str);
    printf("sse = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE]));
    printf("sse2 = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE2]));
    printf("sse3 = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE3]));
    printf("ssse3 = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSSE3]));
    printf("sse4.1 = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE4_1]));
    printf("sse4.2 = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE4_2]));
    printf("sse4a = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_SSE4A]));
    printf("avx = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_AVX]));
    printf("movbe = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_MOVBE]));
    printf("popcnt = %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_X86_POPCNT]));
#endif
}

} // namespace platform_info
} // namespace cxxporthelper

#endif
