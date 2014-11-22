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

#include <cxxporthelper/platform_info.hpp>

namespace cxxporthelper {
namespace platform_info {

const platform_info_provider &get_platform_info_provider_instance() CXXPH_NOEXCEPT
{
    static const platform_info_provider provider = platform_info_provider();
    return provider;
};

#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)
extern void
i386_x86_64_collect_platform_info(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features) CXXPH_NOEXCEPT;
#define COLLECT_PLATFORM_INFO(features) i386_x86_64_collect_platform_info(features)
#elif(CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64)
extern void
arm_collect_platform_info(std::bitset<platform_info_provider::NUM_FEATURE_INDICES> &features) CXXPH_NOEXCEPT;
#define COLLECT_PLATFORM_INFO(features) arm_collect_platform_info(features)
#else
#define COLLECT_PLATFORM_INFO(features)
#endif

platform_info_provider::platform_info_provider() : feature_flags_(0) { COLLECT_PLATFORM_INFO(feature_flags_); }

platform_info_provider::~platform_info_provider() {}

} // namespace platform_info
} // namespace cxxporthelper
