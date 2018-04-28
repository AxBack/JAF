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
			Math::Matrix offset;
		};

		struct Burst
		{
			UINT nrParticles;
			Behaviour* pBehaviour;
		};

		struct Trail
		{
			float interval;
			Behaviour* pBehaviour;
		};

		Updater* m_pUpdater;

		int m_nrRelevantParticles { 0 };
		int m_rocketCounter {0 };
		bool m_active { false };

		std::queue<Rocket> m_rockets;

		Burst m_burst;
		Trail m_trail;

	protected:

		void fire(Behaviour* pBehaviour, const Math::Matrix& offset);
		void fireRelevant(Behaviour* pBehaviour, const Math::Matrix& offset, int type = -1);

	public:

		Sequence(Updater* pUpdater)
				: m_pUpdater(pUpdater)
		{}

		bool active() const { return m_active; }

		void addRocket(float offsetTime, Behaviour* pBehaviour, const Math::Matrix& offset)
		{
			pBehaviour->incrementUsers();
			m_rockets.push({offsetTime, pBehaviour, offset});
		}

		void addBurst(UINT nrParticles, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_burst.nrParticles = nrParticles;
			m_burst.pBehaviour = pBehaviour;
		}

		void addTrail(float interval, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_trail.interval = interval;
			m_trail.pBehaviour = pBehaviour;
		}

		virtual void onDead(const Particle* pParticle) override;
		virtual void onInterval(const Particle* pParticle) override;

		void start();
		void update(float dt);

	};
}