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

#
# definitions
#

# NOTE: this function is used to avoid MATH_PATH(=260) issue on Windows...
cxxph-normalize-path = $(shell $(HOST_PYTHON) -c "import os.path; print os.path.abspath(\"$(firstword $1)\").replace(\"\\\\\", \"/\")")

#
# cxxporthelper Library (libcxxporthelper)
#
MY_DIR := $(call my-dir)
CXXPORTHELPER_TOP_DIR := $(call cxxph-normalize-path, $(MY_DIR)/../../../..)

LOCAL_PATH := $(CXXPORTHELPER_TOP_DIR)

include $(CLEAR_VARS)

# clear local variables
SHARED_C_INCLUDES := $(LOCAL_PATH)/include
SHARED_CFLAGS := 

LOCAL_MODULE := cxxporthelper_static
LOCAL_MODULE_FILENAME := cxxporthelper
LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/source/*.cpp)
LOCAL_C_INCLUDES := $(SHARED_C_INCLUDES)

# if $(TARGET_ARCH_ABI) == {armeabi | armeabi-v7a | armeabi-v7a-hard | arm64-v8a}
ifneq (, $(filter armeabi armeabi-v7a armeabi-v7a-hard arm64-v8a, $(TARGET_ARCH_ABI)))
    LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/source/arm__arm64/*.cpp)
endif

# if $(TARGET_ARCH_ABI) == {x86 | x86_64}
ifneq (, $(filter x86 x86_64, $(TARGET_ARCH_ABI)))
    LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/source/x86__x86_64/*.cpp)
endif

# remove unnecessary $(LOCAL_PATH)
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, $(LOCAL_SRC_FILES))

SHARED_CFLAGS += $(CXXPH_CFLAGS_$(TARGET_ARCH_ABI))

LOCAL_C_INCLUDES := \
    $(SHARED_C_INCLUDES) \
    $(NDK_ROOT)/sources/android/cpufeatures

LOCAL_CFLAGS := \
    $(SHARED_CFLAGS)

LOCAL_STATIC_LIBRARIES := cpufeatures

# export
LOCAL_EXPORT_C_INCLUDES := $(SHARED_C_INCLUDES)
LOCAL_EXPORT_CFLAGS := $(SHARED_CFLAGS)

# clear local variables
SHARED_C_INCLUDES :=
SHARED_CFLAGS := 

include $(BUILD_STATIC_LIBRARY)
