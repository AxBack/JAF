#pragma once

#include <string>
#include <android/asset_manager.h>
#include "../../pch.h"
#include <sstream>
#include <exception>
#include <stdexcept>

namespace JAWE { namespace GFX {

	class Shader {
	protected:

		static bool verifyShader(GLuint shader) {
			GLint param = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
			if (param == GL_FALSE) {
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
				GLchar *pLog = new GLchar[param];
				glGetShaderInfoLog(shader, param, nullptr, pLog);
				_loge("verifyShader( %s )", pLog);
				_safe_delete_array(pLog);
			}
			return true;
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

		static GLuint createShader(AAssetManager* pAssetManager, const char* file, GLint type)
		{
			std::string f;
			if (!loadFile(pAssetManager, file, f))
				return GL_FALSE;

			const char *pFile = f.c_str();

			GLuint handle = glCreateShader(type);
			glShaderSource(handle, 1, &pFile, nullptr);
			glCompileShader(handle);
			if (!verifyShader(handle))
				return GL_FALSE;

			return handle;
		}

		static GLuint createProgram(AAssetManager *pAssetManager, const char* vsFile, const char* psFile)        {

			GLuint vs = createShader(pAssetManager, vsFile, GL_VERTEX_SHADER);
			GLuint ps = createShader(pAssetManager, psFile, GL_FRAGMENT_SHADER);

			GLuint program = createProgram(vs, ps);

			glDeleteShader(vs);
			glDeleteShader(ps);

			return program;
		}

		static GLuint createProgram(GLuint vs, GLuint ps)
		{
			GLuint program = glCreateProgram();
			glAttachShader(program, vs);
			glAttachShader(program, ps);
			glLinkProgram(program);

			glDetachShader(program, vs);
			glDetachShader(program, ps);

			GLint param = 0;
			glGetProgramiv(program, GL_LINK_STATUS, &param);
			if (param == GL_FALSE) {
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &param);
				GLchar *pLog = new GLchar[param];
				glGetProgramInfoLog(program, param, nullptr, pLog);
				_loge("init( %s )", pLog);
				_safe_delete_array(pLog);
				return GL_FALSE;
			}
			return program;
		}

		static GLint getLocation(GLuint program, const char* uniform)
		{
			GLint location = glGetUniformLocation(program, uniform);
			if(location < 0)
			{
				_logd("uniform (%s) not found.", uniform);
				std::stringstream ss;
				ss << uniform << " not found in shader";
				return -1;
			}
			return location;
		}

	public:

		Shader()
		{
		}

		virtual ~Shader() {
			release();
		}

		virtual void release() {};
	};
}}
