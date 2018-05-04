#include "director.h"

#include "updater.h"

namespace JAF {

	void Director::init(std::mt19937& generator, Updater* pUpdater)
	{
		m_pSequence.reset(new Sequence(pUpdater));
	}

	void Director::update(float dt)
	{
		if(m_pSequence->nrActiveRockets() < Settings::minNrRockets())
		{
			m_creator.create(*m_pSequence.get());
			m_pSequence->start();
		}

		m_pSequence->update(dt);
	}
}

