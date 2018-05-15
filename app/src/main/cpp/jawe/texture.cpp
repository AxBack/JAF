#include "texture.h"

namespace JAWE {

    bool Texture::init(GLenum format, GLsizei width, GLsizei height, const unsigned char* pPixels)
    {
        m_nrHandles = 1;
        m_pHandles = std::unique_ptr<GLuint[]>(new GLuint[m_nrHandles]);
        glGenTextures(m_nrHandles, m_pHandles.get());

        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_pHandles[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pPixels);
        Util::setupTexture(GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }
}