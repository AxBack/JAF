#include "sequence.h"

#include "updater.h"
#include "../jawe/random.h"

namespace JAF {

	void Sequence::fire(Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factors)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->fire(nullptr, pBehaviour, pOffset);
	}

	void Sequence::fireRelevant(Behaviour* pBehaviour, matrix_ptr pOffset, int type, const Math::Vector3& factors)
	{
		++m_nrRelevantParticles;
		Particle* p = m_pUpdater->fireParticle();
		p->setType(type);
		p->setInterval(m_trail.interval);
		p->fire(this, pBehaviour, pOffset);
	}

	void Sequence::start()
	{

	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;
        if (pParticle->getType() == 84)
        {
			matrix_ptr p = pParticle->calculateTransform();
			for(UINT i=0; i < m_burst.nrParticles; ++i)
			{
				float x = JAWE::Random::randf(-180.0f, 180.0f);
				float z = JAWE::Random::randf(-180.0f, 180.0f);

				matrix_ptr offset(new Math::Matrix);
				Math::Matrix& t = *offset.get();
				Math::Matrix::setRotate(t, x, 0, z);
				t = *p.get() * t;

				fire(m_burst.pBehaviour, offset);
			}
        }
	}

	void Sequence::onInterval(const Particle* pParticle)
	{
		matrix_ptr p = pParticle->calculateTransform();
		Math::Vector3 factors {JAWE::Random::randf(-1.0f, 1.0f), 1, JAWE::Random::randf(-1.0f, 1.0f)};
		fire(m_trail.pBehaviour, p, factors);
	}

	void Sequence::update(float dt)
	{
		if(m_rockets.size() > 0)
		{
			m_rockets.front().offsetTime -= dt;
			if(m_rockets.front().offsetTime <= 0)
			{
				Rocket& r = m_rockets.front();
				fireRelevant(r.pBehaviour, r.pTransform, 84, r.factors);
				m_rockets.pop();
			}
		}
	}

}