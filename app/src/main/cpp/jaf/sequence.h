#pragma once

#include "particle.h"

namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

        typedef std::shared_ptr<Math::Matrix> matrix_ptr;

		Updater* m_pUpdater;

		int m_nrRelevantParticles { 0 };

		//temp
		const Behaviour* m_pBehaviour { nullptr };

	protected:

		void fire(const Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factor = {1,1,1}) const;
		void fireRelevant(const Behaviour* pBehaviour, matrix_ptr pOffset, int type = -1, const Math::Vector3& factor = {1,1,1});

	public:

		Sequence(Updater* pUpdater, const Behaviour* pBehaviour)
				: m_pUpdater(pUpdater)
				, m_pBehaviour(pBehaviour)
		{}

		bool active() const { return m_nrRelevantParticles > 0; }

		virtual void onDead(const Particle* pParticle) override;

		void start();
		void update(float dt);

	};
}