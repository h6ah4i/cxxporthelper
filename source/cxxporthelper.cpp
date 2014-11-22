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

#include <cxxporthelper/cxxporthelper.hpp>
#include <cxxporthelper/platform_info.hpp>

namespace cxxporthelper {

bool cxxporthelper_init()
{
    // initialize platform_info_provider singleton instance
    // (workaround for C++11 not fully implemented compiler)
    (void)platform_info::get_platform_info_provider_instance();

    return true;
}
}
