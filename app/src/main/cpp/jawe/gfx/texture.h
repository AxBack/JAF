#pragma once

#include <string>
#include <android/asset_manager.h>
#include <memory>
#include "../utils.h"
#include "../io/png_loader.h"

namespace JAWE { namespace GFX {

	class Texture
	{
	protected:
		GLuint m_handle { UINT_MAX };

	public:

		virtual ~Texture()
		{
			clear();
		}

		void clear()
		{
			if(m_handle < UINT_MAX)
				glDeleteTextures(1, &m_handle);
		}

		bool init(GLenum format, GLsizei width, GLsizei height, const unsigned char* pPixels);
		bool load(const char* file, IO::PngLoader* pLoader);

		void bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_handle);
		}
	};

}}