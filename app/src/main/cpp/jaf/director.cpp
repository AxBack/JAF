#include "director.h"

#include "updater.h"

namespace JAF {

	void Director::init(std::mt19937& generator)
	{
		float time = 1.0f;
		m_rocketSettings.vec3Paths.push_back(createPath(time, 2, (Math::Vector3[]){{0,0,0}, {-300,600,-300}}));
		m_rocketSettings.vec3Paths.push_back(createPath(time, 2, (Math::Vector3[]){{0,0,0}, {300,600,300}}));

		m_rocketSettings.floatPaths.push_back(createPath(time, 1, (float[]){1}));

		m_rocketSettings.colorPaths.push_back(createPath(time, 2, (Math::Color[]){{1,0,0,1}, {0,1,0,1}}));
		m_rocketSettings.colorPaths.push_back(createPath(time, 2, (Math::Color[]){{1,1,0,1}, {1,0,1,1}}));

		{
			Behaviour b;
			b.init(time);
			b.addPosition(1.0f, &m_rocketSettings.vec3Paths[0]);
			b.addPosition(1.0f, &m_rocketSettings.vec3Paths[1]);
			b.addSize(1.0f, &m_rocketSettings.floatPaths[0]);
			b.addColor(1.0f, &m_rocketSettings.colorPaths[0]);
			b.addColor(1.0f, &m_rocketSettings.colorPaths[1]);
			m_rocketBehaviours.push_back(b);
		}

		m_flareSettings.vec3Paths.push_back(createPath(time, 2, (Math::Vector3[]){{0,0,0}, {0,100,0}}));
		m_flareSettings.floatPaths.push_back(createPath(time, 4, (float[]){0.1, 0.5, 0.5, 0}));
		m_flareSettings.colorPaths.push_back(createPath(time, 2, (Math::Color[]){{1,1,0,1}, {1,1,1,1}}));

		{
			Behaviour b;
			b.init(time);
			b.addPosition(1.0f, &m_flareSettings.vec3Paths[0]);
			b.addSize(1.0f, &m_flareSettings.floatPaths[0]);
			b.addColor(1.0f, &m_flareSettings.colorPaths[0]);
			m_flareBehaviours.push_back(b);
		}

		m_trailSettings.vec3Paths.push_back(createPath(time, 2, (Math::Vector3[]){{0,0,0}, {0,-150,0}}));
		m_trailSettings.vec3Paths.push_back(createPath(time, 2, (Math::Vector3[]){{0,0,0}, {-50,-50,-50}}));
		m_trailSettings.floatPaths.push_back(createPath(time, 2, (float[]){1, 0.0}));
		m_trailSettings.colorPaths.push_back(createPath(time, 2, (Math::Color[]){{1,1,1,1}, {0,0,0,0}}));

		{
			Behaviour b;
			b.init(time);
			b.addPosition(1.0f, &m_trailSettings.vec3Paths[0]);
			b.addPosition(1.0f, &m_trailSettings.vec3Paths[1]);
			b.addSize(1.0f, &m_trailSettings.floatPaths[0]);
			b.addColor(1.0f, &m_trailSettings.colorPaths[0]);
			m_trailBehaviours.push_back(b);
		}

		m_generator = generator;
	}

	void Director::update(Updater* pUpdater, float dt)
	{
		if(m_pSequence == nullptr)
		{
			m_pSequence.reset(new Sequence(pUpdater, &m_rocketBehaviours[0], &m_flareBehaviours[0], &m_trailBehaviours[0]));
			m_creator.create(*m_pSequence.get());
			m_pSequence->start();
		}

		m_pSequence->update(dt);

		if(!m_pSequence->active())
			m_pSequence = nullptr;

	}
}

