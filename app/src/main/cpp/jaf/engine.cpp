#include "engine.h"
#include "../jawe/io/png_loader.h"
#include "../jawe/gfx/cube_texture.h"

namespace JAF {

    bool Engine::onInit(AAssetManager *pAssetManager)
    {
        _logi("JAF::Engine( Init begin: %d )", m_id);

		if(!setupParticles(pAssetManager))
			return false;

		if(!setupPostProcess(pAssetManager))
			return false;

		if(!setupSkybox(pAssetManager))
			return false;

		float w = 1080.0f;
		float h = 1920.0f;
        m_camera.setProjection(w, h);
        m_camera.updateView(Vector3(0,0,-100), Vector3(0,0,0), Vector3(0,1,0));

		m_bloomShader.updateSize(w, h);
		m_swapChain.init(4, w, h, true, JAWE::GFX::Framebuffer::READ_WRITE);
		for(int i=0; i<4; ++i)
		{
			m_swapChain.set();
			m_swapChain.clear();
			m_swapChain.step();
		}

        if(!m_updater.init())
            return false;

		m_sensor.init(m_id);

		JAWE::IO::PngLoader loader(pAssetManager);
		JAWE::GFX::CubeTexture t;
		if(!t.load("skybox/", &loader))
			return false;

		m_fadeIn.init(-1, 1);

        _logi("JAF::Engine( Init end: %d )", m_id);
        return true;
    }

    bool Engine::setupParticles(AAssetManager* pAssetManager)
    {
		_logi("JAF::Engine( SetupParticles begin: %d )", m_id);

        PositionVertex vertices[] = {
                {-1, 0, 0}, {0, 0.5f, 0}, {1, 0, 0}, {0, -0.5f, 0},
				{0, 1, 0}, {0.5f, 0, 0}, {0, -1, 0}, {-0.5f, 0, 0}
        };

        GLushort indices[] = {0,1,2, 0,2,3, 4,5,6, 4,6,7};

        if(!m_particleMesh.init(8, vertices, 12, indices))
            return false;

        if (!m_particleShader.init(pAssetManager, m_particleMesh))
            return false;

		_logi("JAF::Engine( SetupParticles end: %d )", m_id);

		return true;
    }

	bool Engine::setupPostProcess(AAssetManager* pAssetManager)
	{
		_logi("JAF::Engine( setupPostProcess begin: %d )", m_id);

		TexturedVertex vertices[] = {
				{-1,-1,0,0,0},
				{ 1,-1,0,1,0},
				{ 1, 1,0,1,1},
				{-1, 1,0,0,1}
		};

		GLushort indices[] = {0, 1, 2, 0, 2, 3};

		if(!m_screenMesh.init(4, vertices, 6, indices))
			return false;

		if (!m_bloomShader.init(pAssetManager, m_screenMesh))
			return false;

		_logi("JAF::Engine( setupPostProcess end: %d )", m_id);

		return true;
	}

	bool Engine::setupSkybox(AAssetManager* pAssetManager)
	{
		_logi("JAF::Engine( setupSkybox begin: %d )", m_id);

		PositionVertex vertices[] = {
				{-1,-1,0},
				{ 1,-1,0},
				{ 1, 1,0},
				{-1, 1,0}
		};

		GLushort indices[] = {0, 1, 2, 0, 2, 3};

		if(!m_skyboxMesh.init(4, vertices, 6, indices))
			return false;

		if(!m_skyboxShader.init(pAssetManager, m_skyboxMesh))
			return false;

		_logi("JAF::Engine( setupSkybox end: %d )", m_id);

		return true;
	}

    bool Engine::onRender()
	{
		if(!Settings::interactive() && !m_updater.isRunning())
			m_updater.resume();

        if (m_sizeChanged)
        {
            m_sizeChanged = false;
            m_camera.setProjection(m_viewport[2], m_viewport[3]);
			m_bloomShader.updateSize(m_viewport[2], m_viewport[3]);
			m_swapChain.init(4, m_viewport[2], m_viewport[3], true, JAWE::GFX::Framebuffer::READ_WRITE);
			for(int i=0; i<4; ++i)
			{
				m_swapChain.set();
				m_swapChain.clear();
				m_swapChain.step();
			}
        }

		if(m_rotationSpan != Settings::rotationSpan())
		{
			m_rotation.clear();
			m_rotationSpan = static_cast<float>(Settings::rotationSpan());
			float points[] = { m_rotationSpan*0.5f, m_rotationSpan*-0.5f };
			m_rotation.add(1.0f, 2, points);
		}

		m_updater.updateInstances(m_particleMesh);
		m_sensor.update();
		JAWE::MATH::Vector3 at = {0,0,1};

		if(Settings::immersive())
		{
			if(!m_sensor.active())
				m_sensor.resume();

			JAWE::MATH::Vector3 r = m_sensor.getDelta();
			m_yaw = m_tiltRange.clamp(m_yaw + r.x());
			m_pitch = m_tiltRange.clamp(m_pitch + r.y());
			JAWE::MATH::Quaternion pitch = JAWE::MATH::Quaternion::fromAxisAngle({1, 0, 0}, m_tiltPath.traverse( m_yaw + 90));
			JAWE::MATH::Quaternion yaw = JAWE::MATH::Quaternion::fromAxisAngle({0, 1, 0}, -m_tiltPath.traverse(m_pitch + 90));
			//JAWE::MATH::Quaternion roll = JAWE::MATH::Quaternion::fromAxisAngle({0, 0,1}, r.z()* 0.1f);

			at = Matrix::transform(Matrix::setRotate(pitch * yaw), at, 0.0);
		}
		else if(m_sensor.active())
			m_sensor.pause();

		JAWE::MATH::Quaternion yaw = Quaternion::fromAxisAngle(0,1,0, m_rotation.traverse(m_offset));
		Matrix rot;
		Matrix::setRotate(rot,  yaw);
		Vector3 pos = Matrix::transform(rot, {0,1000,-1000});
		at = Matrix::transform(rot, at, 0.0f);
		Vector3 up = Matrix::transform(rot, {0,1,0}, 0.0f);

		m_camera.updateView(pos, pos + at, up);
        m_camera.update();

        glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);

        glClearColor(0,0,0,0);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_skyboxShader.render(m_camera, m_skyboxMesh, m_fadeIn.advance());

		m_swapChain.step();
		m_swapChain.set();
		m_swapChain.clear();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

        if (m_particleMesh.hasInstances())
		{
			m_particleShader.render(m_camera, m_particleMesh);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);

			m_bloomShader.render(m_screenMesh, m_swapChain, 1.0f);
		}

        return true;
    }
}
