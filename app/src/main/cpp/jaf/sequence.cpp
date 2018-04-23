#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fire(Updater* pUpdater, const Behaviour* pBehaviour, matrix_ptr pOffset, int type) const
	{
		pUpdater->fireParticle(nullptr, pBehaviour, pOffset, type);
	}

	void Sequence::fireRelevant(Updater* pUpdater, const Behaviour* pBehaviour, matrix_ptr pOffset, int type)
	{
		++m_nrRelevantParticles;
		pUpdater->fireParticle(this, pBehaviour, pOffset, type);
	}

	void Sequence::start(Updater* pUpdater)
	{
		//temp
        matrix_ptr p(new Math::Matrix);
        p->setIdentity();
        p->translate(0,-300,0);
		fireRelevant(pUpdater, m_pBehaviour, p, 84);
	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;

        if (pParticle->getType() == 84)
        {

        }
	}

	void Sequence::update(Updater* pUpdater, float dt)
	{

	}

}