#pragma once

#include "../jawe/engine.h"
#include "vertex.h"

#include "../jawe/mesh.h"
#include "../jawe/camera.h"
#include "../jawe/shader.h"
#include "particle_shader.h"
#include "updater.h"

namespace JAF {

    class Engine : public JAWE::Engine
    {
    private:

        typedef Math::Vector3 Vector3;
        typedef Math::Matrix Matrix;
        typedef Math::Quaternion Quaternion;
        typedef JAWE::Path<float> float_path;

        Updater m_updater;

        std::atomic_bool m_sizeChanged;

        std::atomic<float> m_offset;

        JAWE::Camera m_camera;
        float_path m_rotation;

        ParticleShader m_particleShader;
        JAWE::InstancedMesh<PositionVertex, ParticleInstance> m_particleMesh;

    public:

        Engine()
            : JAWE::Engine()
            , m_sizeChanged(false)
            , m_offset(0.5f)
        {
            {
                float points[] = { -90, 90 };
                m_rotation.add(1.0f, 2, points);
            }
        }

        virtual ~Engine()
        {
        }

        virtual bool init(AAssetManager *pAssetManager) override;

        virtual bool render() override;

        virtual void resume() override { }

        virtual void pause() override { }

        virtual void setOffset(float x, float y) override
        {
            m_offset = x;
        }

        virtual void updateSize(int width, int height) override
        {
            JAWE::Engine::updateSize(width, height);
            m_sizeChanged = true;
        }

    };

}