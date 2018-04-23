#pragma once

#include "particle.h"
namespace JAF {

	class Updater;

	class Sequence : public ParticleListener
	{
	private:

        typedef std::shared_ptr<Math::Matrix> matrix_ptr;

		int m_nrRelevantParticles { 0 };

		//temp
		const Behaviour* m_pBehaviour { nullptr };

	protected:

		void fire(Updater* pUpdater, const Behaviour* pBehaviour, matrix_ptr pOffset, int type = 0) const;
		void fireRelevant(Updater* pUpdater, const Behaviour* pBehaviour, matrix_ptr pOffset, int type = 0);

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