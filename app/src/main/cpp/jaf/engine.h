#pragma once

#include "../jawe/engine.h"
#include "vertex.h"

#include "../jawe/gfx/mesh.h"
#include "../jawe/camera.h"
#include "../jawe/gfx/shader.h"
#include "particle_shader.h"
#include "updater.h"
#include "bloom_shader.h"
#include "../jawe/counter.h"
#include "animator.h"
#include "../jawe/sensor.h"
#include "../jawe/gfx/swap_chain.h"
#include "skybox_shader.h"

namespace JAF {

    class Engine : public JAWE::Engine
    {
    private:

		template <typename K> struct Range
		{
			K min, max;
			K clamp(K v) { return std::min(max, std::max(v, min)); }
		};

        typedef JAWE::MATH::Vector3 Vector3;
        typedef JAWE::MATH::Matrix Matrix;
        typedef JAWE::MATH::Quaternion Quaternion;
        typedef JAWE::Path<float> float_path;

		JAWE::Sensor m_sensor;
        Updater m_updater;

        std::atomic_bool m_sizeChanged { false };

        std::atomic<float> m_offset { 0.5f };

        JAWE::Camera m_camera;
        float_path m_rotation;
		float m_rotationSpan { 0 };

		Range<float> m_tiltRange = {-90, 90};
		float_path m_tiltPath;
		float m_yaw {0};
		float m_pitch {0};

        ParticleShader m_particleShader;
        JAWE::GFX::InstancedMesh<PositionVertex, ParticleInstance> m_particleMesh;

		JAWE::GFX::SwapChain m_swapChain;

		BloomShader m_bloomShader;
		JAWE::GFX::Mesh<TexturedVertex> m_screenMesh;

		JAWE::GFX::Mesh<PositionVertex> m_skyboxMesh;
		SkyboxShader m_skyboxShader;

		Animator m_fadeIn;

        bool setupParticles(AAssetManager* pAssetManager);
        bool setupPostProcess(AAssetManager* pAssetManager);
		bool setupSkybox(AAssetManager* pAssetManager);

	protected:

		virtual bool onInit(AAssetManager *pAssetManager) override;
		virtual bool onRender() override;

		virtual void onResume() override
		{
			m_yaw = m_pitch = 0.0f;
			if(Settings::immersive())
				m_sensor.resume();
			m_updater.resume();
			m_fadeIn.start();
		}

		virtual void onPause() override
		{
			m_yaw = m_pitch = 0.0f;
			if(m_sensor.active())
				m_sensor.pause();
			m_updater.pause();
		}

		virtual void onTap(float x, float y) override
		{
			if(Settings::interactive() == TAP)
			{
				if(m_updater.isRunning())
					m_updater.pause();
				else
					m_updater.resume();
			}
		}

		virtual void onDoubleTap(float x, float y) override
		{
			if(Settings::interactive() == DOUBLE_TAP)
			{
				if(m_updater.isRunning())
					m_updater.pause();
				else
					m_updater.resume();
			}
		}

		virtual void onOffset(float x, float y) override
		{
			m_offset = x;
		}

    public:

        Engine()
            : JAWE::Engine()
            , m_camera(1.0f, 2000.0f)
        {
			{
				float points[] = {-10, -2, 0, 2, 10};
				m_tiltPath.add(180, 5, points);
			}
        }

        virtual ~Engine()
        {
            m_updater.pause();
        }

        virtual void updateSize(int width, int height) override
        {
            JAWE::Engine::updateSize(width, height);
            m_sizeChanged = true;
        }

    };
}