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

#ifndef CXXPORTHELPER_CSTDINT_HPP_
#define CXXPORTHELPER_CSTDINT_HPP_

#include <cxxporthelper/impl/cxxporthelper_config.hpp>

#if CXXPH_CONFIG_USE_STLPORT
#include <stdint.h>

namespace cxxporthelper {
namespace cstdint {
typedef ::int8_t int8_t;
typedef ::int16_t int16_t;
typedef ::int32_t int32_t;
typedef ::int64_t int64_t;
typedef ::int_fast8_t int_fast8_t;
typedef ::int_fast16_t int_fast16_t;
typedef ::int_fast32_t int_fast32_t;
typedef ::int_fast64_t int_fast64_t;
typedef ::int_least8_t int_least8_t;
typedef ::int_least16_t int_least16_t;
typedef ::int_least32_t int_least32_t;
typedef ::int_least64_t int_least64_t;
typedef ::intmax_t intmax_t;
typedef ::intptr_t intptr_t;
typedef ::uint8_t uint8_t;
typedef ::uint16_t uint16_t;
typedef ::uint32_t uint32_t;
typedef ::uint64_t uint64_t;
typedef ::uint_fast8_t uint_fast8_t;
typedef ::uint_fast16_t uint_fast16_t;
typedef ::uint_fast32_t uint_fast32_t;
typedef ::uint_fast64_t uint_fast64_t;
typedef ::uint_least8_t uint_least8_t;
typedef ::uint_least16_t uint_least16_t;
typedef ::uint_least32_t uint_least32_t;
typedef ::uint_least64_t uint_least64_t;
typedef ::uintmax_t uintmax_t;
typedef ::uintptr_t uintptr_t;
} // anespace cstdint
} // namespace cxxporthelper

namespace std {
using namespace cxxporthelper::cstdint;
}

#else
#include <cstdint>
#endif

#endif // CXXPORTHELPER_CSTDINT_HPP_
