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

		JAWE::MATH::Matrix m_offset;

	protected:

		void fireRelevant(Behaviour* pBehaviour, const JAWE::MATH::Matrix& offset, int type = -1);

	public:

		Sequence(Updater* pUpdater)
				: m_pUpdater(pUpdater)
		{
			m_offset.setIdentity();
		}

		int nrActiveRockets() const { return static_cast<int>(m_nrActiveRockets + m_rockets.size()); }

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