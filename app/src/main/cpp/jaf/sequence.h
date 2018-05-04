#pragma once

#include <queue>
#include "particle.h"

namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

		struct Rocket
		{
			float offsetTime;
			Behaviour* pBehaviour;
		};

		Updater* m_pUpdater;

		int m_nrActiveRockets { 0 };

		std::queue<Rocket> m_rockets;

		Math::Matrix m_offset;

	protected:

		void fireRelevant(Behaviour* pBehaviour, const Math::Matrix& offset, int type = -1);

	public:

		Sequence(Updater* pUpdater)
				: m_pUpdater(pUpdater)
		{
			m_offset.setIdentity();
			m_offset.translate(0,-1000,0);
		}

		int nrActiveRockets() const { return m_nrActiveRockets; }

		void addRocket(float offsetTime, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_rockets.push({offsetTime, pBehaviour});
		}

		virtual void onDead(const Particle* pParticle) override;

		void start();
		void update(float dt);

	};
}