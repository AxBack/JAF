#include "director.h"

#include "updater.h"

namespace JAF {

	void Director::init(std::mt19937& generator, Updater* pUpdater)
	{
		m_generator = generator;
		m_pSequence.reset(new Sequence(pUpdater));
	}

	void Director::update(float dt)
	{
		if(!m_pSequence->active())
		{
			m_creator.create(*m_pSequence.get());
			m_pSequence->start();
		}

		m_pSequence->update(dt);
	}
}

