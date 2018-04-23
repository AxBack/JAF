#pragma once

#include "../jawe/shader.h"
#include "vertex.h"
#include "../jawe/mesh.h"
#include "../jawe/camera.h"

namespace JAF {

    class ParticleShader : public JAWE::Shader
    {
    private:

        typedef JAWE::InstancedMesh<PositionVertex, ParticleInstance> Mesh;

        GLuint m_program { 0 };
        GLuint m_vao { 0 };
        GLint m_viewProjectionLocation { -1 };
        GLint m_rightLocation { -1 };
        GLint m_upLocation { -1 };

    public:

        bool init(AAssetManager *pAssetManager, const Mesh& mesh);

        virtual void release() override {
            if (m_program > 0) {
                glDeleteProgram(m_program);
                m_program = 0;
            }

            if (m_vao > 0) {
                glDeleteVertexArrays(1, &m_vao);
                m_vao = 0;
            }
        }

        void render(const JAWE::Camera& camera, const Mesh& mesh) {
            glUseProgram(m_program);
            glBindVertexArray(m_vao);
            glUniformMatrix4fv(m_viewProjectionLocation, 1, GL_FALSE, camera.getViewProjection().data());
            glUniform3fv(m_upLocation, 1, camera.getUp().data());
            glUniform3fv(m_rightLocation, 1, camera.getRight().data());
            mesh.render();
        }
    };
}