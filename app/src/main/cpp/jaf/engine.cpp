#include "engine.h"

namespace JAF {

    bool Engine::init(AAssetManager *pAssetManager) {
        {
            PositionVertex vertices[] = {
                    {-0.5f, 0.5f,  0},
                    {0.5f,  0.5f,  0},
                    {0.5f,  -0.5f, 0},
                    {-0.5f, -0.5f, 0}
            };

            GLushort indices[] = {0, 1, 2, 0, 2, 3};

            if(!m_particleMesh.init(4, vertices, 6, indices))
                return false;

            if (!m_particleShader.init(pAssetManager, m_particleMesh))
                return false;
        }

        m_camera.updateProjection(1080,1920);
        m_camera.updateView(Vector3(0,0,-100), Vector3(0,0,0), Vector3(0,1,0));

        return true;
    }

    bool Engine::render() {

        if (m_sizeChanged)
        {
            m_sizeChanged = false;
            m_camera.updateProjection(m_viewport[2], m_viewport[3]);
        }

        {
            ParticleInstance instance = {0,0,0, 10, 1,1,1,1};
            m_particleMesh.updateInstances(1, &instance);
        }

        m_camera.update();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);

        glClearColor(0,0,0,0);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        m_particleShader.render(m_camera, m_particleMesh);

        return true;
    }
}
