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

#ifndef CXXPORTHELPER_ATOMIC_HPP_
#define CXXPORTHELPER_ATOMIC_HPP_

#include <cxxporthelper/impl/cxxporthelper_config.hpp>

#if CXXPH_CONFIG_USE_STLPORT
#include <cxxporthelper/impl/atomic_compat.hpp>

namespace std {
using namespace cxxporthelper::atomic_compat;
}

#else
#include <atomic>
#endif

#endif // CXXPORTHELPER_ATOMIC_HPP_
