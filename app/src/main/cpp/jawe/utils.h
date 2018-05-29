#pragma once

#include <android/asset_manager.h>
#include <string>
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
			_logd(ready ? "SIMD::enabled" : "SIMD::disable");
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

    static bool loadFile(AAssetManager *pAssetManager, const std::string &asset, std::string &outFile) {
        AAsset *pAsset = AAssetManager_open(pAssetManager, asset.c_str(),
                                            AASSET_MODE_STREAMING);
        if (pAsset == nullptr) {
            _loge("loadFile( Could not get asset: %s )", asset.c_str());
            return false;
        }

        outFile.clear();

        static const size_t size = 1024;
        int r = 0;
        char *pBuffer = new char[size];
        while ((r = AAsset_read(pAsset, pBuffer, size)) > 0) {
            outFile.insert(outFile.end(), pBuffer, pBuffer + r);
        }
        AAsset_close(pAsset);

        _safe_delete_array(pBuffer);
        return true;
    }
}