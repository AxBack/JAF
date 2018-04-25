#pragma once

#include <queue>
#include "particle.h"

namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

        typedef std::shared_ptr<Math::Matrix> matrix_ptr;

		struct Rocket
		{
			float offsetTime;
			matrix_ptr pTransform;
			Math::Vector3 factors;
		};

		Updater* m_pUpdater;

		int m_nrRelevantParticles { 0 };

		std::queue<Rocket> m_rockets;

		//temp
		const Behaviour* m_pRocket { nullptr };
		const Behaviour* m_pFlare { nullptr };
		const Behaviour* m_pTrail { nullptr };

	protected:

		void fire(const Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factor = {1,1,1});
		void fireRelevant(const Behaviour* pBehaviour, matrix_ptr pOffset, int type = -1, const Math::Vector3& factor = {1,1,1});

	public:

		Sequence(Updater* pUpdater, const Behaviour* pRocket, const Behaviour* pFlare, const Behaviour* pTrail)
				: m_pUpdater(pUpdater)
				, m_pRocket(pRocket)
				, m_pFlare(pFlare)
				, m_pTrail(pTrail)
		{}

		bool active() const { return m_nrRelevantParticles > 0; }

		void add(float offsetTime, std::shared_ptr<Math::Matrix> p, const Math::Vector3& factors) { m_rockets.push({offsetTime, p, factors}); }

		virtual void onDead(const Particle* pParticle) override;
		virtual void onInterval(const Particle* pParticle) override;

		void start();
		void update(float dt);

	};
}