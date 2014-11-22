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

#ifndef CXXPORTHELPER_UTILITY_HPP_
#define CXXPORTHELPER_UTILITY_HPP_

#include <cxxporthelper/impl/cxxporthelper_config.hpp>

#include <utility>

#if CXXPH_CONFIG_USE_STLPORT

#include <cxxporthelper/type_traits>
#include <cxxporthelper/compiler.hpp>

namespace cxxporthelper {
namespace utility {

// STLPort does not provides std::move() and std::forward()

//
// move
//
template <typename T>
typename std::remove_reference<T>::type &&move(T &&x) CXXPH_NOEXCEPT
{
    return static_cast<typename std::remove_reference<T>::type &&>(x);
}

//
// forward
//
template <typename T>
T &&forward(typename std::remove_reference<T>::type &x) CXXPH_NOEXCEPT
{
    return static_cast<T &&>(x);
}

template <typename T>
T &&forward(typename std::remove_reference<T>::type &&x) CXXPH_NOEXCEPT
{
    return static_cast<T &&>(x);
}

} // namespace complex
} // namespace cxxporthelper

namespace std {
using namespace ::cxxporthelper::utility;
}

#endif // CXXPH_CONFIG_USE_STLPORT

#endif // CXXPORTHELPER_UTILITY_HPP_
