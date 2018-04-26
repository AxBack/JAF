#include "director.h"

#include "updater.h"

namespace JAF {

	void Director::init(std::mt19937& generator)
	{
		m_generator = generator;
	}

	void Director::update(Updater* pUpdater, float dt)
	{
		if(m_pSequence == nullptr)
		{
			m_pSequence.reset(new Sequence(pUpdater));
			m_creator.create(*m_pSequence.get());
			m_pSequence->start();
		}

		m_pSequence->update(dt);

		if(!m_pSequence->active())
			m_pSequence = nullptr;

	}
}

