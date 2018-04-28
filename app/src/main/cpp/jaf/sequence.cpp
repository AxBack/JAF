#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fire(Behaviour* pBehaviour, const Math::Matrix& offset)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->fire(nullptr, pBehaviour, offset);
	}

	void Sequence::fireRelevant(Behaviour* pBehaviour, const Math::Matrix& offset, int type)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->setType(type);
		p->setInterval(m_trail.interval);
		p->fire(this, pBehaviour, offset);
	}

	void Sequence::start()
	{
		m_active = true;
		m_nrRelevantParticles = static_cast<int>(m_rockets.size());
		m_rocketCounter = 0;
	}

	void Sequence::onDead(const Particle* pParticle)
	{
		Math::Matrix t = pParticle->calculateTransform();
		for(UINT i=0; i < m_burst.nrParticles; ++i)
		{
			fire(m_burst.pBehaviour, t);
		}

		if(m_nrRelevantParticles == pParticle->getType())
		{
			m_active = false;
			m_burst.pBehaviour->decrementUsers();
			m_burst.pBehaviour = nullptr;
			m_trail.pBehaviour->decrementUsers();
			m_trail.pBehaviour = nullptr;
		}
	}

	void Sequence::onInterval(const Particle* pParticle)
	{
		Math::Matrix t = pParticle->calculateTransform();
		fire(m_trail.pBehaviour, t);
	}

	void Sequence::update(float dt)
	{
		if(m_rockets.size() > 0)
		{
			m_rockets.front().offsetTime -= dt;
			if(m_rockets.front().offsetTime <= 0)
			{
				Rocket& r = m_rockets.front();
				fireRelevant(r.pBehaviour, m_offset, ++m_rocketCounter);
				r.pBehaviour->decrementUsers();
				m_rockets.pop();
			}
		}
	}

}