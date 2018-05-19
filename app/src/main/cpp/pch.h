#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string.h>
#include <android/log.h>
#include <cpu-features.h>

#define SAFE_DELETE( p ) { if( p ) { delete ( p ); ( p ) = nullptr; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete [] ( p ); ( p ) = nullptr; } }

#define BUFFER_OFFSET(i) ((char *)NULL + (i * 4))

#define UINT unsigned int

#define LOG_TAG "jaf"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define TO_RADIANS(degrees) ((degrees) * static_cast<float>(M_PI) / 180.0f)
#define TO_DEGREES(radians) ((radians) * 180.0f / static_cast<float>(M_PI))

#if defined(__ARM_NEON)

static bool SIMD_READY = false;
static void verifySIMD()
{
	uint32_t family = android_getCpuFamily();
	SIMD_READY = (family == ANDROID_CPU_FAMILY_ARM || family == ANDROID_CPU_FAMILY_ARM64)
				&& (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON) != 0;

	LOGD(SIMD_READY ? "SIMD::enabled" : "SIMD::disable");
}

#endif
