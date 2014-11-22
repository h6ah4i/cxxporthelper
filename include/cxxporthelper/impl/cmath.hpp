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

#ifndef CXXPORTHELPER_CMATH_HPP_
#define CXXPORTHELPER_CMATH_HPP_

#include <cxxporthelper/compiler.hpp>

#if CXXPH_COMPILER_IS_MSVC
#define _USE_MATH_DEFINES
#include <math.h> // !!! This is required to avoid the include guard of the cmath header
#include <cmath>
#else
#include <cmath>
#endif

#endif // CXXPORTHELPER_CMATH_HPP_
