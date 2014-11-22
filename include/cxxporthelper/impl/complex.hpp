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

#ifndef CXXPORTHELPER_COMPLEX_HPP_
#define CXXPORTHELPER_COMPLEX_HPP_

#include <cxxporthelper/impl/cxxporthelper_config.hpp>

#include <complex>

namespace cxxporthelper {
namespace complex {

#if CXXPH_CONFIG_USE_STLPORT
// STLPort provides perior C++11 version of std::complex,
// setter version of real() and imag() methods are not exist...

template <typename T>
void set_real(std::complex<T> &c, typename std::complex<T>::value_type x) CXXPH_NOEXCEPT
{
    c._M_re = x;
}

template <typename T>
void set_imag(std::complex<T> &c, typename std::complex<T>::value_type x) CXXPH_NOEXCEPT
{
    c._M_im = x;
}
#else
template <typename T>
void set_real(std::complex<T> &c, typename std::complex<T>::value_type x) CXXPH_NOEXCEPT
{
    c.real(x);
}

template <typename T>
void set_imag(std::complex<T> &c, typename std::complex<T>::value_type x) CXXPH_NOEXCEPT
{
    c.imag(x);
}
#endif

} // namespace complex
} // namespace cxxporthelper

#endif // CXXPORTHELPER_COMPLEX_HPP_/
