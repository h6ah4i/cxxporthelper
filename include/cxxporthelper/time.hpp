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

#ifndef CXXPORTHELPER_TIME_HPP_
#define CXXPORTHELPER_TIME_HPP_

#include <cxxporthelper/compiler.hpp>

#include <time.h>

#if CXXPH_TARGET_PLATFORM == CXXPH_PLATFORM_ANDROID

#include <android/api-level.h>

#if __ANDROID_API__ == 9999 // Android L

// declare mising APIs
extern "C" int clock_settime(clockid_t, const struct timespec *) __LIBC_ABI_PUBLIC__;
extern "C" int clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *) __LIBC_ABI_PUBLIC__;

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7
#define CLOCK_REALTIME_ALARM 8
#define CLOCK_BOOTTIME_ALARM 9

#endif
#endif

#endif // CXXPORTHELPER_TIME_HPP_
