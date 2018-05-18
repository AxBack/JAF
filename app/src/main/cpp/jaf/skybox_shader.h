#pragma once

#include "../jawe/shader.h"
#include "../jawe/mesh.h"
#include "vertex.h"
#include "../jawe/camera.h"
#include "../jawe/cube_texture.h"

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

        JAWE::CubeTexture m_texture;

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

        void render(const JAWE::Camera& camera, const Mesh& mesh)
        {
            glUseProgram(m_program);

            glActiveTexture(GL_TEXTURE0);
            m_texture.bind();
            glUniform1f(m_textureLocation, 0);

            glBindVertexArray(m_vao);
            glUniform3fv(m_forwardLocation, 1, camera.getForward().data());
            glUniform3fv(m_upLocation, 1, camera.getUp().data());
            glUniform3fv(m_rightLocation, 1, camera.getRight().data());
            mesh.render();
        }
    };
}