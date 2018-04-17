#pragma once

#include "../jawe/engine.h"
#include "vertex.h"

#include "../jawe/mesh.h"
#include "../jawe/camera.h"
#include "../jawe/shader.h"
#include "particle_shader.h"

namespace JAF {

    class Engine : public JAWE::Engine
    {
    private:

        typedef Math::Vector3 Vector3;

        std::atomic_bool m_sizeChanged;

        JAWE::Camera m_camera;

        ParticleShader m_particleShader;
        JAWE::InstancedMesh<PositionVertex, ParticleInstance> m_particleMesh;

    public:

        Engine()
            : JAWE::Engine()
            , m_sizeChanged(false)
        {
        }

        virtual ~Engine()
        {
        }

        virtual bool init(AAssetManager *pAssetManager) override;

        virtual bool render() override;

        virtual void resume() override { }

        virtual void pause() override { }

        virtual void updateSize(int width, int height)
        {
            JAWE::Engine::updateSize(width, height);
            m_sizeChanged = true;
        }

    };

}