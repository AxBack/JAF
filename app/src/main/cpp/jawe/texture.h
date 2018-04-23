#pragma once

#include <string>
#include <android/asset_manager.h>
#include <memory>
#include "util.h"

namespace JAWE {

	class Texture
	{
	protected:
		GLsizei m_nrHandles { 1 };
		std::unique_ptr<GLuint[]> m_pHandles;

	public:

		virtual ~Texture()
		{
			clear();
		}

		void clear()
		{
			if(m_pHandles)
				glDeleteTextures(1, m_pHandles.get());
			m_pHandles = nullptr;
		}

		bool init(GLenum format, GLsizei width, GLsizei height, const char* pPixels)
		{
			m_nrHandles = 1;
			m_pHandles = std::unique_ptr<GLuint[]>(new GLuint[m_nrHandles]);
			glGenTextures(m_nrHandles, m_pHandles.get());

			glActiveTexture(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, m_pHandles[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pPixels);
			Util::setupTexture(GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

		void bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_pHandles[0]);
		}
	};

};