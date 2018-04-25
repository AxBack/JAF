#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "sequence.h"

namespace JAF {

	class SequenceCreator
	{
	private:

		enum FACTOR_TYPE { SAME, OPPOSITE, OPPOSITE_X, OPPOSITE_Z };

		BalancedCollection<int> m_nrRockets;
		BalancedCollection<float> m_intervals;
		BalancedCollection<FACTOR_TYPE> m_factors;

	public:

		SequenceCreator()
		{
			m_nrRockets.push(1);
			m_nrRockets.push(2);
			m_nrRockets.push(3);
			m_nrRockets.push(4);

			m_intervals.push(0.0f);
			m_intervals.push(0.5f);
			m_intervals.push(1.0f);
			m_intervals.push(2.0f);

			m_factors.push(SAME);
			m_factors.push(OPPOSITE);
			m_factors.push(OPPOSITE_X);
			m_factors.push(OPPOSITE_Z);
		}

		void create(Sequence& out);

	};

};