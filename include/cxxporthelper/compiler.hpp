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

#ifndef CXXPORTHELPER_COMPILER_HPP_
#define CXXPORTHELPER_COMPILER_HPP_

//
// compiler detection
//
#define CXXPH_COMPILER_TYPE_UNKNOWN 0
#define CXXPH_COMPILER_TYPE_GCC 1
#define CXXPH_COMPILER_TYPE_CLANG 2
#define CXXPH_COMPILER_TYPE_MSVC 3

#if defined(__clang__)
#define CXXPH_DETECTED_COMPILER_TYPE CXXPH_COMPILER_TYPE_CLANG
#elif defined(__GNUC__)
#define CXXPH_DETECTED_COMPILER_TYPE CXXPH_COMPILER_TYPE_GCC
#elif defined(_MSC_VER)
#define CXXPH_DETECTED_COMPILER_TYPE CXXPH_COMPILER_TYPE_MSVC
#else
#warning unknown compiler
#define CXXPH_DETECTED_COMPILER_TYPE CXXPH_COMPILER_TYPE_UNKNOWN
#endif

#define CXXPH_COMPILER_IS_CLANG (CXXPH_DETECTED_COMPILER_TYPE == CXXPH_COMPILER_TYPE_CLANG)
#define CXXPH_COMPILER_IS_GCC (CXXPH_DETECTED_COMPILER_TYPE == CXXPH_COMPILER_TYPE_GCC)
#define CXXPH_COMPILER_IS_MSVC (CXXPH_DETECTED_COMPILER_TYPE == CXXPH_COMPILER_TYPE_MSVC)

//
// GCC version code
//
#if CXXPH_COMPILER_IS_GCC
#define CXXPH_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#define CXXPH_GCC_VERSION 0
#endif

//
// Compatibility macros
//
#if CXXPH_COMPILER_IS_MSVC
// ### Visual Studio ###

// Visual Studio 2013 doesn't support "constexpr", "noexcept", "aligneas"
#define CXXPH_COMPILER_SUPPORTS_CONSTEXPR 0
#define CXXPH_COMPILER_SUPPORTS_NOEXCEPT 0
#define CXXPH_COMPILER_SUPPORTS_ALIGNAS 0

#elif CXXPH_COMPILER_IS_GCC
// ### GCC ###
#define CXXPH_COMPILER_SUPPORTS_CONSTEXPR 1
#define CXXPH_COMPILER_SUPPORTS_NOEXCEPT 1
#if CXXPH_GCC_VERSION >= 40800 /* GCC4.8 >= */
#define CXXPH_COMPILER_SUPPORTS_ALIGNAS 1
#else
#define CXXPH_COMPILER_SUPPORTS_ALIGNAS 0
#endif
#else
// ### OTHER ###
#define CXXPH_COMPILER_SUPPORTS_CONSTEXPR 1
#define CXXPH_COMPILER_SUPPORTS_NOEXCEPT 1
#define CXXPH_COMPILER_SUPPORTS_ALIGNAS 1
#endif

// "noexcept" keyword
#if CXXPH_COMPILER_SUPPORTS_NOEXCEPT
#define CXXPH_NOEXCEPT noexcept
#else
#define CXXPH_NOEXCEPT throw()
#endif

// "alignas" modifier
#if CXXPH_COMPILER_SUPPORTS_ALIGNAS
#define CXXPH_ALIGNAS(alignment) alignas(alignment)
#elif CXXPH_COMPILER_IS_GCC || CXXPH_COMPILER_IS_CLANG
#define CXXPH_ALIGNAS(alignment) __attribute__((aligned(alignment)))
#elif CXXPH_COMPILER_IS_MSVC
#define CXXPH_ALIGNAS(alignment) __declspec(align(alignment))
#else
#error
#endif

// "constexpr" keyword (optional)
#if CXXPH_COMPILER_SUPPORTS_CONSTEXPR
#define CXXPH_OPTIONAL_CONSTEXPR constexpr
#else
#define CXXPH_OPTIONAL_CONSTEXPR
#endif

// "restrict" keyword
#define CXXPH_RESTRICT __restrict

// "noinline" attribute
#if CXXPH_COMPILER_IS_MSVC
#define CXXPH_ATTR_NOINLINE __declspec(noinline)
#else
#define CXXPH_ATTR_NOINLINE __attribute__((noinline))
#endif

// likely() & unlikely
#if CXXPH_COMPILER_IS_GCC || CXXPH_COMPILER_IS_CLANG
#define CXXPH_LIKELY(x) __builtin_expect(!!(x), true)
#define CXXPH_UNLIKELY(x) __builtin_expect(!!(x), false)
#else
#define CXXPH_LIKELY(x) (x)
#define CXXPH_UNLIKELY(x) (x)
#endif

// __has_builtin() macro
#ifndef __has_builtin
#define __has_builtin(x) 0 // Compatibility with non-clang compilers.
#endif

//
// Target archtecture types
//
#define CXXPH_ARCH_UNKNOWN 0
#define CXXPH_ARCH_I386 1
#define CXXPH_ARCH_X86_64 2
#define CXXPH_ARCH_ARM 3
#define CXXPH_ARCH_ARM64 4
#define CXXPH_ARCH_MIPS 5
#define CXXPH_ARCH_POWERPC 6

//
// Target platform types
//
#define CXXPH_PLATFORM_UNKNOWN 0
#define CXXPH_PLATFORM_LINUX 1
#define CXXPH_PLATFORM_UNIX 2
#define CXXPH_PLATFORM_WINDOWS 3
#define CXXPH_PLATFORM_OSX 4
#define CXXPH_PLATFORM_ANDROID 5
#define CXXPH_PLATFORM_IOS 6
#define CXXPH_PLATFORM_IOS_SIMULATOR 7

//
// CXXPH_TARGET_ARCH macro
//
#if defined(__x86_64__) || defined(_M_X64)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_X86_64
#elif defined(__i386__) || defined(_M_IX86)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_I386
#elif defined(__aarch64__)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_ARM64
#elif defined(__arm__)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_ARM
#elif defined(__mips__)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_MIPS
#elif defined(__ppc__)
#define CXXPH_TARGET_ARCH CXXPH_ARCH_POWERPC
#else
#define CXXPH_TARGET_ARCH CXXPH_ARCH_UNKNOWN
#endif

//
// CXXPH_TARGET_PLATFORM macro
//
#if defined(_WIN64) || defined(_WIN32)
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#if TARGET_OS_IPHONE && TARGET_OS_EMBEDDED
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_IOS
#elif TARGET_OS_IPHONE && !TARGET_OS_EMBEDDED
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_IOS_SIMULATOR
#elif defined(__MACH__)
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_OSX
#else
#warning Unknown platform
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_UNKNOWN
#endif
#elif defined(ANDROID) || defined(__ANDROID__)
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_ANDROID
#elif defined(__linux__)
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_LINUX
#elif defined(__unix__)
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_UNIX
#else
#warning Unknown platform
#define CXXPH_TARGET_PLATFORM CXXPH_PLATFORM_UNKNOWN
#endif

#define CXXPH_PLATFORM_SIMD_ALIGNMENT 64  // == max(x86, x86_64, aarch32, aarch64) simd alignment size
#define CXXPH_PLATFORM_CACHE_LINE_SIZE 64 // == max(x86, x86_64, aarch32, aarch64) cache size

//
// platform specific features
//
#if (CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) /* MMX doesn't work on x86_64 mode */ &&                                    \
    (CXXPH_COMPILER_IS_MSVC || defined(__MMX__))
#define CXXPH_COMPILER_SUPPORTS_X86_MMX 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_MMX 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE2__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE2 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE2 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE3__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE3 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE3 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSSE3__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSSE3 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSSE3 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE4_1__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4_1 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4_1 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE4_2__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4_2 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4_2 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__SSE4A__))
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4A 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_SSE4A 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX2__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX2 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX2 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512F__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512F 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512F 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512DQ__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512DQ 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512DQ 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512BW__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512BW 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512BW 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512VL__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512VL 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512VL 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512CD__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512CD 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512CD 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512ER__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512ER 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512ER 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__AVX512PF__))
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512PF 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_AVX512PF 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__FMA__))
#define CXXPH_COMPILER_SUPPORTS_X86_FMA 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_FMA 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_I386) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_X86_64)) &&                            \
    (CXXPH_COMPILER_IS_MSVC || defined(__FMA4__))
#define CXXPH_COMPILER_SUPPORTS_X86_FMA4 1
#else
#define CXXPH_COMPILER_SUPPORTS_X86_FMA4 0
#endif

#if ((CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM) && defined(__ARM_NEON__)) || (CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64)
#define CXXPH_COMPILER_SUPPORTS_ARM_NEON 1
#else
#define CXXPH_COMPILER_SUPPORTS_ARM_NEON 0
#endif

//
// ARM architecture version
//
#if CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM
#if defined(__ARM_ARCH_2__)
#define CXXPH_ARM_ARCH_VERSION 2
#elif defined(__ARM_ARCH_3__) | defined(__ARM_ARCH_3M__)
#define CXXPH_ARM_ARCH_VERSION 3
#elif defined(__ARM_ARCH_4T__)
#define CXXPH_ARM_ARCH_VERSION 4
#elif defined(__ARM_ARCH_5__) | defined(__ARM_ARCH_5E__) | defined(__ARM_ARCH_5T__) | defined(__ARM_ARCH_5TE__) |      \
    defined(__ARM_ARCH_5TEJ__)
#define CXXPH_ARM_ARCH_VERSION 5
#elif defined(__ARM_ARCH_6__) | defined(__ARM_ARCH_6J__) | defined(__ARM_ARCH_6K__) | defined(__ARM_ARCH_6Z__) |       \
    defined(__ARM_ARCH_6ZK__) | defined(__ARM_ARCH_6T2__)
#define CXXPH_ARM_ARCH_VERSION 6
#elif defined(__ARM_ARCH_7__) | defined(__ARM_ARCH_7A__) | defined(__ARM_ARCH_7R__) | defined(__ARM_ARCH_7M__) |       \
    defined(__ARM_ARCH_7S__)
#define CXXPH_ARM_ARCH_VERSION 7
#else
#error Unsupported ARM processor
#endif
#elif CXXPH_TARGET_ARCH == CXXPH_ARCH_ARM64
#define CXXPH_ARM_ARCH_VERSION 8
#else
#define CXXPH_ARM_ARCH_VERSION 0
#endif

//
// Workarounds
//
#ifdef CXXPORTHELPER_WORKAROUND_CLION_IDE
#undef CXXPH_RESTRICT
#define CXXPH_RESTRICT /* CLion IDE does not recognize __restrict keyword */
#endif

#endif // CXXPORTHELPER_COMPILER_HPP_
