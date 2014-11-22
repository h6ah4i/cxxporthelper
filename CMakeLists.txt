#
#    Copyright (C) 2014 Haruki Hasegawa
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

cmake_minimum_required(VERSION 2.8)

### Project: cxxporthelper
project(cxxporthelper)

set(CMAKE_BUILD_TYPE Release)

## enable C++11
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

set(LIB_CXXPORTHELPER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source LIB_CXXPORTHELPER_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/arm__arm64 LIB_CXXPORTHELPER_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/x86__x86_64 LIB_CXXPORTHELPER_SOURCES)

add_library(cxxporthelper STATIC ${LIB_CXXPORTHELPER_SOURCES})

target_include_directories(cxxporthelper
    PUBLIC $<BUILD_INTERFACE:${LIB_CXXPORTHELPER_INCLUDE_DIR}>
)
