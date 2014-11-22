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

#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64)

#include <cxxporthelper/cstdint>
#include <cxxporthelper/platform_info.hpp>

#if CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_ANDROID
#include <cpu-features.h>
#endif

#if CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_LINUX
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#endif

// #define CPUID_DEBUG
#ifdef CPUID_DEBUG
#include <cstdio>
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

#if CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_ANDROID
// Android
static void arm_collect_platform_info_impl(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features)
{
    typedef platform_info_provider::feature_index_t flags;

    const AndroidCpuFamily cpu_family = android_getCpuFamily();
    const uint64_t cpu_features = android_getCpuFeatures();

#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM
    if (cpu_family == ANDROID_CPU_FAMILY_ARM) {
        features.set(flags::FEATURE_INDEX_ARM_V7, (cpu_features & ANDROID_CPU_ARM_FEATURE_ARMv7) ? 1 : 0);
        features.set(flags::FEATURE_INDEX_ARM_VFP_V3, (cpu_features & ANDROID_CPU_ARM_FEATURE_VFPv3) ? 1 : 0);
        features.set(flags::FEATURE_INDEX_ARM_NEON, (cpu_features & ANDROID_CPU_ARM_FEATURE_NEON) ? 1 : 0);
    }
#endif

#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64
    if (cpu_family == ANDROID_CPU_FAMILY_ARM64) {
        features.set(flags::FEATURE_INDEX_ARM_NEON, (cpu_features & ANDROID_CPU_ARM64_FEATURE_ASIMD) ? 1 : 0);
    }
#endif
}
#elif CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_LINUX
// Linux

static bool starts_with(const std::string &str1, const std::string &str2)
{
    return (str1.compare(0, str2.size(), str2) == 0);
}

static std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> res;
    std::string::size_type current = 0, found;

    while ((found = str.find_first_of(delim, current)) != std::string::npos) {
        res.push_back(std::string(str, current, found - current));
        current = found + 1;
    }

    res.push_back(std::string(str, current, str.size() - current));

    return res;
}

static void arm_collect_platform_info_impl(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features)
{
    typedef platform_info_provider::feature_index_t flags;

    std::ifstream ifs_cpuinfo("/proc/cpuinfo");

    if (!ifs_cpuinfo) {
        return;
    }

    const std::string features_prefix("Features\t");
    const std::string cpu_arch_prefix("CPU architecture:");

    std::vector<std::string> features_list;
    int cpu_arch_no = 0;

    std::string line;
    while (std::getline(ifs_cpuinfo, line)) {
        if (starts_with(line, features_prefix)) {
            const std::string::size_type colon_pos = line.find_first_of(':');

            if (colon_pos != std::string::npos) {
                features_list = split(line.substr(colon_pos + 1), ' ');
            }
        } else if (starts_with(line, cpu_arch_prefix)) {
            const std::string::size_type colon_pos = line.find_first_of(':');

            if (colon_pos != std::string::npos) {
                char *endptr = nullptr;
                const long l = strtol(&line[colon_pos + 1], &endptr, 10);
                if (endptr && ((*endptr) == '\0')) {
                    cpu_arch_no = l;
                }
            }
        }
    }

    if (cpu_arch_no == 7) {
        features.set(flags::FEATURE_INDEX_ARM_V7, 1);
    }

    for (const auto &flag : features_list) {
#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM
        if (flag == "neon") {
            features.set(flags::FEATURE_INDEX_ARM_NEON, 1);
        } else if (flag == "vfpv3") {
            features.set(flags::FEATURE_INDEX_ARM_VFP_V3, 1);
        }
#endif
#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64
        if (flag == "asimd") {
            features.set(flags::FEATURE_INDEX_ARM_NEON, 1);
        }
#endif
    }
}
#elif CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_IOS
static void arm_collect_platform_info_impl(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features)
{
    typedef platform_info_provider::feature_index_t flags;

#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM
    // TODO
    features.set(flags::FEATURE_INDEX_ARM_V7, 1);
    features.set(flags::FEATURE_INDEX_ARM_VFP_V3, 1);
    features.set(flags::FEATURE_INDEX_ARM_NEON, 1);
#endif

#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64
    // TODO
    features.set(flags::FEATURE_INDEX_ARM_NEON, (cpu_features & ANDROID_CPU_ARM64_FEATURE_ASIMD) ? 1 : 0);
#endif
}
#else
// for other platforms
static void arm_collect_platform_info_impl(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features) {}
#endif

void arm_collect_platform_info(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features)
{
    arm_collect_platform_info_impl(features);

#ifdef CPUID_DEBUG
    typedef platform_info_provider::feature_index_t flags;

    printf("armv7 - %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_ARM_V7]));
    printf("vfpv3 - %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_ARM_VFP_V3]));
    printf("neon - %d\n", static_cast<bool>(features[flags::FEATURE_INDEX_ARM_NEON]));
#endif
}

} // namespace platform_info
} // namespace cxxporthelper

#endif
