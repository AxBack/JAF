#include "skybox_shader.h"

namespace JAF {

#define FORWARD "cameraNormal"
#define UP "cameraUp"
#define RIGHT "cameraRight"
#define TEXTURE "uTexture"

    bool SkyboxShader::init(AAssetManager *pAssetManager, const JAF::SkyboxShader::Mesh &mesh)
    {
        JAWE::PngLoader loader(pAssetManager);
        if(!m_texture.load("skybox/", &loader))
            return false;

        m_program = createProgram(pAssetManager, "shaders/skybox_vs.glsl", "shaders/skybox_fs.glsl");

        m_textureLocation = getLocation(m_program, TEXTURE);
        m_forwardLocation = getLocation(m_program, FORWARD);
        m_upLocation = getLocation(m_program, UP);
        m_rightLocation = getLocation(m_program, RIGHT);

        glGenVertexArrays(1, &m_vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexBuffer());
        glBindBuffer(GL_ARRAY_BUFFER, mesh.getStaticBuffer());

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PositionVertex), nullptr);

        glBindVertexArray(0);

        return true;
    }

}