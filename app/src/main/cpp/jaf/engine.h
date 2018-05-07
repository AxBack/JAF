#pragma once

#include "../jawe/engine.h"
#include "vertex.h"

#include "../jawe/mesh.h"
#include "../jawe/camera.h"
#include "../jawe/shader.h"
#include "particle_shader.h"
#include "updater.h"
#include "bloom_shader.h"
#include "../jawe/counter.h"

namespace JAF {

    class Engine : public JAWE::Engine
    {
    private:

        typedef Math::Vector3 Vector3;
        typedef Math::Matrix Matrix;
        typedef Math::Quaternion Quaternion;
        typedef JAWE::Path<float> float_path;

        Updater m_updater;

        std::atomic_bool m_sizeChanged { false };

        std::atomic<float> m_offset { 0.5f };
        float m_extra { 0 };

        JAWE::Camera m_camera;
        float_path m_rotation;

		JAWE::Counter m_counter;

        ParticleShader m_particleShader;
        JAWE::InstancedMesh<PositionVertex, ParticleInstance> m_particleMesh;

		BloomShader m_bloomShader;
		JAWE::Mesh<TexturedVertex> m_screenMesh;
		JAWE::Framebuffer m_bloomTarget;

        bool setupParticles(AAssetManager* pAssetManager);
        bool setupPostProcess(AAssetManager* pAssetManager);

    public:

        Engine()
            : JAWE::Engine()
            , m_camera(1.0f, 2000.0f)
        {
            {
                float points[] = { 90, -90 };
                m_rotation.add(1.0f, 2, points);
            }
        }

        virtual ~Engine()
        {
            m_updater.pause();
        }

        virtual bool init(AAssetManager *pAssetManager) override;

        virtual bool render() override;

        virtual void resume() override { m_counter.step(); m_updater.resume(); }

        virtual void pause() override { m_updater.pause(); }

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