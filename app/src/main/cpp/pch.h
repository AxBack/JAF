#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string.h>
#include <android/log.h>
#include <cpu-features.h>

#define _safe_delete( p ) { if( p ) { delete ( p ); ( p ) = nullptr; } }
#define _safe_delete_array( p ) { if( p ) { delete [] ( p ); ( p ) = nullptr; } }

#define _buffer_offset(i) ((char *)NULL + (i * 4))

#define UINT unsigned int

#define LOG_TAG "jaf"

#define _loge(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define _logw(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define _logd(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define _logi(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define _to_radians(degrees) ((degrees) * static_cast<float>(M_PI) / 180.0f)
#define _to_degrees(radians) ((radians) * 180.0f / static_cast<float>(M_PI))

#define _lock(x) std::lock_guard<std::mutex> _(x)
#define _for_each(v) for(auto& it : v)