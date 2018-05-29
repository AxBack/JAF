#pragma once

#include "../jawe/gfx/shader.h"
#include "../jawe/gfx/mesh.h"
#include "vertex.h"
#include "../jawe/camera.h"
#include "../jawe/gfx/cube_texture.h"

namespace JAF {

    class SkyboxShader : public JAWE::GFX::Shader
    {
    private:

        typedef JAWE::GFX::Mesh<PositionVertex> Mesh;

        GLuint m_program { 0 };
        GLuint m_vao { 0 };

        GLint m_textureLocation;
        GLint m_forwardLocation;
        GLint m_rightLocation;
        GLint m_upLocation;
        GLint m_arLocation;

        JAWE::GFX::CubeTexture m_texture;

    public:

        bool init(AAssetManager* pAssetManager, const Mesh& mesh);

        virtual void release() override
        {
            if (m_program > 0) {
                glDeleteProgram(m_program);
                m_program = 0;
            }

            if (m_vao > 0) {
                glDeleteVertexArrays(1, &m_vao);
                m_vao = 0;
            }
        }

        void render(const JAWE::Camera& camera, const Mesh& mesh);
    };
}