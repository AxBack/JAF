#include "sequence_creator.h"

namespace JAF {

	void SequenceCreator::createRockets(Sequence& out)
	{
		std::shared_ptr<Behaviour> pBehaviour = m_rocketCreator.create();

		std::shared_ptr<Math::Matrix> pTransform(new Math::Matrix);
		pTransform->setIdentity();
		pTransform->translate(0,-1000,0);

		int nrRockets = m_nrRockets.front();
		if(nrRockets == 1)
		{
			out.addRocket(0.0f, pBehaviour, pTransform, {1,1,1});
			return;
		}

		float interval = m_intervals.front();
		FACTOR_TYPE factor = m_factors.front();

		switch(factor)
		{
			default:
			case SAME:
				for(int i=0; i<nrRockets; ++i)
					out.addRocket(interval, pBehaviour, pTransform, {1,1,1});
				break;
			case OPPOSITE:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.addRocket(interval, pBehaviour, pTransform, {f, 1, f});
				}
				break;
			case OPPOSITE_X:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.addRocket(interval, pBehaviour, pTransform, {f, 1, 1});
				}
				break;
			case OPPOSITE_Z:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.addRocket(interval, pBehaviour, pTransform, {1, 1, f});
				}
				break;
		}
	}

	void SequenceCreator::createBursts(Sequence& out)
	{
		out.addBurst(m_nrParticlesPerBurst.front(), m_burstCreator.create());
	}

	void SequenceCreator::createTrails(Sequence& out)
	{
		out.addTrail(m_trailCreator.create());
	}

	void SequenceCreator::create(Sequence& out)
	{
		createRockets(out);
		createBursts(out);
		createTrails(out);
	}

}