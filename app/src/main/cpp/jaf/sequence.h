#pragma once

#include "particle.h"
namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

		int m_nrRelevantParticles { 0 };

		//temp
		const Behaviour* m_pBehaviour { nullptr };

	protected:

		void fire(Updater* pUpdater, const Behaviour* pBehaviour, const Math::Vector3& offset) const;
		void fireRelevant(Updater* pUpdater, const Behaviour* pBehaviour, const Math::Vector3& offset);

	public:

		Sequence(const Behaviour* pBehaviour)
				: m_pBehaviour(pBehaviour)
		{}

		bool active() const { return m_nrRelevantParticles > 0; }

		virtual void onDead(const Particle* pParticle) override;

		void start(Updater* pUpdater);
		void update(Updater* pUpdater, float dt);

	};
}