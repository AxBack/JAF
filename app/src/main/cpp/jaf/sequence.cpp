#include "sequence.h"

#include "updater.h"
#include "../jawe/random.h"

namespace JAF {

	void Sequence::fire(Behaviour* pBehaviour, const Math::Matrix& offset)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->fire(nullptr, pBehaviour, offset);
	}

	void Sequence::fireRelevant(Behaviour* pBehaviour, const Math::Matrix& offset, int type)
	{
		++m_nrRelevantParticles;
		Particle* p = m_pUpdater->fireParticle();
		p->setType(type);
		p->setInterval(m_trail.interval);
		p->fire(this, pBehaviour, offset);
	}

	void Sequence::start()
	{

	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;
        if (pParticle->getType() == 84)
        {
			Math::Matrix t = pParticle->calculateTransform();
			for(UINT i=0; i < m_burst.nrParticles; ++i)
			{
				fire(m_burst.pBehaviour, t);
			}
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
				fireRelevant(r.pBehaviour, r.offset, 84);
				m_rockets.pop();
			}
		}
	}

}