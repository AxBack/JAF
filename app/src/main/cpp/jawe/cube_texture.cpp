#include "cube_texture.h"

namespace JAWE {

    constexpr CubeTexture::Side CubeTexture::SIDES[];

    bool CubeTexture::loadTexture(const std::string& file, GLuint target, PngLoader* pLoader) const
    {
        Png data {file.c_str()};
        if(!pLoader->load(data))
            return false;

        glTexImage2D(target, 0, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.pPixels.get());
        Util::setupTexture(target, GL_LINEAR, GL_REPEAT);

        return true;
    }

    bool CubeTexture::load(const std::string& path, PngLoader* pLoader)
    {
        clear();

        glGenTextures(1, &m_handle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
        Util::setupTexture(GL_TEXTURE_CUBE_MAP, GL_LINEAR, GL_CLAMP_TO_EDGE);

        for(UINT i=0; i<6; ++i)
        {
            if(!loadTexture(path + SIDES[i].file, SIDES[i].target, pLoader ))
                return false;
        }

        glBindTexture(GL_TEXTURE0, 0);

        return true;
    }
}