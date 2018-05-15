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

		bool init(GLenum format, GLsizei width, GLsizei height, const char* pPixels);
        bool load(AAssetManager* pAssetManager, std::string filename)

		void bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_pHandles[0]);
		}
	};

};