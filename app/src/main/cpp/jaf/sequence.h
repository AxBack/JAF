#pragma once

#include <queue>
#include "particle.h"

namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

        typedef std::shared_ptr<Math::Matrix> matrix_ptr;
		typedef std::shared_ptr<Behaviour> behaviour_ptr;

		struct Rocket
		{
			float offsetTime;
			behaviour_ptr pBehaviour;
			matrix_ptr pTransform;
			Math::Vector3 factors;
		};

		struct Burst
		{
			UINT nrParticles;
			behaviour_ptr pBehaviour;
		};

		struct Trail
		{
			behaviour_ptr pBehaviour;
		};

		Updater* m_pUpdater;

		int m_nrRelevantParticles { 0 };

		std::queue<Rocket> m_rockets;

		Burst m_burst;
		Trail m_trail;

	protected:

		void fire(behaviour_ptr pBehaviour, matrix_ptr pOffset, const Math::Vector3& factor = {1,1,1});
		void fireRelevant(behaviour_ptr pBehaviour, matrix_ptr pOffset, int type = -1, const Math::Vector3& factor = {1,1,1});

	public:

		Sequence(Updater* pUpdater)
				: m_pUpdater(pUpdater)
		{}

		bool active() const { return m_nrRelevantParticles > 0 || m_rockets.size() > 0; }

		void addRocket(float offsetTime, behaviour_ptr pBehaviour, matrix_ptr pTransform, const Math::Vector3& factors)
		{
			m_rockets.push({offsetTime, pBehaviour, pTransform, factors});
		}

		void addBurst(UINT nrParticles, behaviour_ptr pBehaviour)
		{
			m_burst.nrParticles = nrParticles;
			m_burst.pBehaviour = pBehaviour;
		}

		void addTrail(behaviour_ptr pBehaviour)
		{
			m_trail.pBehaviour = pBehaviour;
		}

		virtual void onDead(const Particle* pParticle) override;
		virtual void onInterval(const Particle* pParticle) override;

		void start();
		void update(float dt);

	};
}