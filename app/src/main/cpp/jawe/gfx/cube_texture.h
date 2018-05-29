#pragma once


#include "texture.h"
#include "../io/png_loader.h"

namespace JAWE { namespace GFX {

    class CubeTexture
    {
    private:

        struct Side
        {
            const char* file;
            GLuint target;
        };

        static constexpr Side SIDES[6] {
            {"p_x.png", GL_TEXTURE_CUBE_MAP_POSITIVE_X},
            {"p_y.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Y},
            {"p_z.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Z},
            {"n_x.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_X},
            {"n_y.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y},
            {"n_z.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z}
        };

        GLuint m_handle { UINT_MAX };

        bool loadTexture(const std::string& file, GLuint target, IO::PngLoader* pLoader) const;

    public:

        virtual ~CubeTexture()
        {
            clear();
        }

        void clear()
        {
            if(m_handle < UINT_MAX)
                glDeleteTextures(1, &m_handle);
            m_handle = UINT_MAX;
        }

        bool load(const std::string& path, IO::PngLoader* pLoader);

        void bind()
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
        }
    };
}}