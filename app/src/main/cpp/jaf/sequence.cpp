#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fireRelevant(Behaviour* pBehaviour, const Math::Matrix& offset, int type)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->setType(type);
		p->setListener(this);
		pBehaviour->start(p, offset);
	}

	void Sequence::start()
	{

	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrActiveRockets;
		if(m_nrActiveRockets < 0)
			throw std::invalid_argument("Too many callbacks");
	}

	void Sequence::update(float dt)
	{
		if(m_rockets.size() > 0)
		{
			m_rockets.front().offsetTime -= dt;
			if(m_rockets.front().offsetTime <= 0)
			{
				++m_nrActiveRockets;
				Rocket& r = m_rockets.front();
				fireRelevant(r.pBehaviour, m_offset);
				r.pBehaviour->decrementUsers();
				m_rockets.pop();
			}
		}
	}

}