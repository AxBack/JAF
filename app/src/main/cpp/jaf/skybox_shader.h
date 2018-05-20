#pragma once

#include "../jawe/shader.h"
#include "../jawe/mesh.h"
#include "vertex.h"
#include "../jawe/camera.h"
#include "../jawe/cube_texture.h"
#include "../jawe/counter.h"
#include "../jawe/range.h"

namespace JAF {

    class SkyboxShader : public JAWE::Shader
    {
    private:

        typedef JAWE::Mesh<PositionVertex> Mesh;

        GLuint m_program { 0 };
        GLuint m_vao { 0 };

        GLint m_textureLocation;
        GLint m_forwardLocation;
        GLint m_rightLocation;
        GLint m_upLocation;
        GLint m_arLocation;
		GLint m_intensityLocation;

        JAWE::CubeTexture m_texture;

        JAWE::Counter m_counter;
		JAWE::Range<float> m_intensityRange { 0.0f, 2.0f };

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