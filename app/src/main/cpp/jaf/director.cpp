#include "director.h"

#include "updater.h"

namespace JAF {

	void Director::init(std::mt19937& generator)
	{
		m_rocketSettings.vec3Paths.push_back(createPath(3.0f, 2, (Math::Vector3[]){{0,0,0}, {-300,600,-300}}));
		m_rocketSettings.vec3Paths.push_back(createPath(3.0f, 2, (Math::Vector3[]){{0,0,0}, {300,600,300}}));

		m_rocketSettings.floatPaths.push_back(createPath(3.0f, 1, (float[]){10}));

		m_rocketSettings.colorPaths.push_back(createPath(3.0f, 2, (Math::Color[]){{1,0,0,1}, {0,1,0,1}}));
		m_rocketSettings.colorPaths.push_back(createPath(3.0f, 2, (Math::Color[]){{1,1,0,1}, {1,0,1,1}}));

		Behaviour b(m_generator);
		b.init(3.0f);
		b.addPosition(1.0f, &m_rocketSettings.vec3Paths[0]);
		b.addPosition(1.0f, &m_rocketSettings.vec3Paths[1]);
		b.addSize(1.0f, &m_rocketSettings.floatPaths[0]);
		b.addColor(1.0f, &m_rocketSettings.colorPaths[0]);
		b.addColor(1.0f, &m_rocketSettings.colorPaths[1]);
		m_rocketBehaviours.push_back(b);

		m_generator = generator;
	}

	void Director::update(Updater* pUpdater, float dt)
	{
		if(m_pSequence == nullptr)
		{
			m_pSequence.reset(new Sequence(&m_rocketBehaviours[0]));
			m_pSequence->start(pUpdater);
		}

		m_pSequence->update(pUpdater, dt);

		if(!m_pSequence->active())
			m_pSequence = nullptr;

	}
}

