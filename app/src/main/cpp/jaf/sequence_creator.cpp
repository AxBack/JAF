#include "sequence_creator.h"

namespace JAF {

	void SequenceCreator::createRockets(Sequence& out)
	{
		RocketBehaviour* pBehaviour = m_rocketCreator.create();

		int nrRockets = m_nrRockets.front();
		float interval = m_intervals.front();
		for(int i = 0; i < nrRockets; ++i)
			out.addRocket(i == 0 ? 0.0f : interval, pBehaviour);

		Math::Vector3 offset = {0,0,0};
		float tag = 0;

		auto type = nrRockets == 1 ? RocketBehaviour::POINT : m_offsets.front();
		switch(type)
		{
			case RocketBehaviour::LINE:
				{
					float x = JAWE::Random::randf(-200, 200);
					float z = JAWE::Random::randf(-200, 200);

					float length = sqrtf(x*x + z*z) * 2;
					tag = length / static_cast<float>(nrRockets-1);
					offset.x(x);
					offset.z(z);
				}
				break;
			case RocketBehaviour::CIRCLE:
			{
				offset.x(JAWE::Random::randf(-200, 200));
				offset.z(JAWE::Random::randf(-200, 200));
				tag = 360.0f / static_cast<float>(nrRockets);
			}
			break;
		}

		pBehaviour->setOffset(type, offset, tag);
		createBursts(pBehaviour);
	}

	void SequenceCreator::createBursts(RocketBehaviour* p)
	{
		UINT nrParticles = m_nrParticles.front();
		UINT nrBursts = m_nrBursts.front();

		float factor = 1.0f / static_cast<float>(nrBursts);
		UINT nr = static_cast<UINT>(static_cast<float>(nrParticles) * factor);

		for(UINT i=0; i<nrBursts; ++i)
			p->add(nr, m_burstCreator.create());
	}

	void SequenceCreator::createTrails(Sequence& out)
	{
		out.addTrail(0.025, m_trailCreator.create());
	}

	void SequenceCreator::create(Sequence& out)
	{
		createRockets(out);
		createTrails(out);
	}

}