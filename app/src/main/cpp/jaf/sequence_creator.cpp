#include "sequence_creator.h"

namespace JAF {

	void SequenceCreator::createRockets(Sequence& out)
	{
		m_rocketCreator.step();
		RocketBehaviour* pBehaviour = m_rocketCreator.create();

		int nrRockets = m_nrRockets.front();
		float interval = m_intervals.front();
		for(int i = 0; i < nrRockets; ++i)
			out.addRocket(i == 0 ? 0.0f : interval, pBehaviour);

		JAWE::MATH::Vector3 offset = {0,0,0};
		float tag = 0;

		auto release = m_offsets.front();
		switch(release.type)
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
				tag = release.tag / static_cast<float>(nrRockets);
			}
			break;
			default:
				break;
		}

		pBehaviour->setOffset(release.type, offset, tag);
	}

	void SequenceCreator::create(Sequence& out)
	{
		if(Settings::maxRocketsPerSequence() != m_nrRockets.size())
		{
			m_nrRockets.clear();
			for(int i=0; i<Settings::maxRocketsPerSequence(); ++i)
				m_nrRockets.push(i+1);
		}

		createRockets(out);
	}

}