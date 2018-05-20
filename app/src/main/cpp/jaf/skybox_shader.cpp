#include "skybox_shader.h"

namespace JAF {

#define FORWARD "cameraNormal"
#define UP "cameraUp"
#define RIGHT "cameraRight"
#define TEXTURE "uTexture"
#define ASPECT_RATIO "ar"

    bool SkyboxShader::init(AAssetManager *pAssetManager, const JAF::SkyboxShader::Mesh &mesh)
    {
        JAWE::PngLoader loader(pAssetManager);
        if(!m_texture.load("skybox/", &loader))
            return false;

        m_program = createProgram(pAssetManager, "shaders/skybox_vs.glsl", "shaders/skybox_ps.glsl");

        m_textureLocation = getLocation(m_program, TEXTURE);
        m_forwardLocation = getLocation(m_program, FORWARD);
        m_upLocation = getLocation(m_program, UP);
        m_rightLocation = getLocation(m_program, RIGHT);
		m_arLocation = getLocation(m_program, ASPECT_RATIO);

        glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexBuffer());
        glBindBuffer(GL_ARRAY_BUFFER, mesh.getStaticBuffer());

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PositionVertex), nullptr);

        glBindVertexArray(0);
        return true;
    }

    void SkyboxShader::render(const JAWE::Camera& camera, const Mesh& mesh)
    {
        glUseProgram(m_program);

        glActiveTexture(GL_TEXTURE0);
        m_texture.bind();
        glUniform1f(m_textureLocation, 0);

        glBindVertexArray(m_vao);
        glUniform3fv(m_forwardLocation, 1, camera.getForward().data());
        glUniform3fv(m_upLocation, 1, camera.getUp().data());
        glUniform3fv(m_rightLocation, 1, camera.getRight().data());
		glUniform1f(m_arLocation, camera.getAspectRatio());
        mesh.render();
    }
}