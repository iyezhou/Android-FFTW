LOCAL_PATH := $(call my-dir)
ROOT_PATH := $(LOCAL_PATH)

include $(call all-subdir-makefiles)
include $(CLEAR_VARS)

LOCAL_PATH = $(ROOT_PATH)
# LOCAL_CFLAGS := -Wall -Wextra

LOCAL_MODULE := FFTW

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_STATIC_LIBRARIES := libfftw3 libfftw3f libfftw3f_threads
LOCAL_SRC_FILES := fftw.c

include $(BUILD_SHARED_LIBRARY)