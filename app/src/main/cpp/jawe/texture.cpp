#include "texture.h"

namespace JAWE {

    bool Texture::init(GLenum format, GLsizei width, GLsizei height, const unsigned char* pPixels)
    {
        glGenTextures(1, &m_handle);

        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pPixels);
		Utils::setupTexture(GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    bool Texture::load(const char *file, PngLoader* pLoader) {
        Png data { file };
        if(!pLoader->load(data))
            return false;

        return init(GL_RGBA, data.width, data.height, data.pPixels.get());
    }
}