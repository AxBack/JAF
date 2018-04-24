#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fire(const Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factor) const
	{
		m_pUpdater->fireParticle(nullptr, pBehaviour, pOffset, -1, factor);
	}

	void Sequence::fireRelevant(const Behaviour* pBehaviour, matrix_ptr pOffset, int type, const Math::Vector3& factor)
	{
		++m_nrRelevantParticles;
		m_pUpdater->fireParticle(this, pBehaviour, pOffset, type, factor);
	}

	void Sequence::start()
	{
		//temp
        matrix_ptr p(new Math::Matrix);
        p->setIdentity();
        p->translate(0,-300,0);
		fireRelevant(m_pBehaviour, p, 84);
	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;
        if (pParticle->getType() == 84)
        {
			matrix_ptr p = pParticle->calculateTransform();
			fire(m_pBehaviour, p, {1,-1,1});
        }
	}

	void Sequence::update(float dt)
	{

	}

}