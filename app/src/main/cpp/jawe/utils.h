#pragma once

#include "../pch.h"

namespace Utils {

	struct SIMD
	{
		static bool ready;
		static void verify()
		{
#if defined(__ARM_NEON)
			uint32_t family = android_getCpuFamily();
			ready = (family == ANDROID_CPU_FAMILY_ARM || family == ANDROID_CPU_FAMILY_ARM64)
						 && (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON) != 0;
#endif
			LOGD(ready ? "SIMD::enabled" : "SIMD::disable");
		}
	};

	static void setupTexture(GLuint target, GLenum filter, GLenum wrap)
	{
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);
	}

	static GLuint createTexture(GLint internalFormat, GLuint format, GLuint type,
								GLsizei width, GLsizei height, GLenum filter, GLenum wrap)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, 0);
		setupTexture(GL_TEXTURE_2D, filter, wrap);
		return texture;
	}
}