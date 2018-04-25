#include "sequence_creator.h"

namespace JAF {

	void SequenceCreator::create(Sequence& out)
	{
		std::shared_ptr<Math::Matrix> p(new Math::Matrix);
		p->setIdentity();
		p->translate(0,-300,0);

		int nrRockets = m_nrRockets.front();
		if(nrRockets == 1)
		{
			out.add(0.0f, p, {1,1,1});
			return;
		}

		float interval = m_intervals.front();
		FACTOR_TYPE factor = m_factors.front();

		switch(factor)
		{
			default:
			case SAME:
				for(int i=0; i<nrRockets; ++i)
					out.add(interval, p, {1,1,1});
				break;
			case OPPOSITE:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.add(interval, p, {f, 1, f});
				}
				break;
			case OPPOSITE_X:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.add(interval, p, {f, 1, 1});
				}
				break;
			case OPPOSITE_Z:
				for(int i=0; i<nrRockets; ++i)
				{
					float f = i%2 == 0 ? 1.0f : -1.0f;
					out.add(interval, p, {1, 1, f});
				}
				break;
		}
	}

}