#include "sequence_creator.h"

namespace JAF {

	void SequenceCreator::createRockets(Sequence& out)
	{
		PathBehaviour* pBehaviour = m_rocketCreator.create();

		Math::Matrix offset;
		offset.setIdentity();
		offset.translate(0, -1000, 0);

		float interval = m_intervals.front();
		int nrRockets = m_nrRockets.front();
		for(int i = 0; i < nrRockets; ++i)
			out.addRocket(interval, pBehaviour, offset);
	}

	void SequenceCreator::createBursts(Sequence& out)
	{
		out.addBurst(m_nrParticlesPerBurst.front(), m_burstCreator.create());
	}

	void SequenceCreator::createTrails(Sequence& out)
	{
		out.addTrail(0.025, m_trailCreator.create());
	}

	void SequenceCreator::create(Sequence& out)
	{
		createRockets(out);
		createBursts(out);
		createTrails(out);
	}

}