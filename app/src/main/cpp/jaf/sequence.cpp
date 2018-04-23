#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fire(Updater* pUpdater, const Behaviour* pBehaviour, const Math::Vector3& offset) const
	{
		pUpdater->fireParticle(nullptr, pBehaviour, offset);
	}

	void Sequence::fireRelevant(Updater* pUpdater, const Behaviour* pBehaviour, const Math::Vector3& offset)
	{
		++m_nrRelevantParticles;
		pUpdater->fireParticle(this, pBehaviour, offset);
	}

	void Sequence::start(Updater* pUpdater)
	{
		//temp
		fireRelevant(pUpdater, m_pBehaviour, {0,-300,0});
	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;
	}

	void Sequence::update(Updater* pUpdater, float dt)
	{

	}

}