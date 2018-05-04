#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "sequence.h"
#include "rocket_creator.h"
#include "trail_creator.h"

namespace JAF {

	class SequenceCreator
	{
	private:

		BalancedCollection<int> m_nrRockets;
		BalancedCollection<float> m_intervals;
		BalancedCollection<RocketBehaviour::OffsetType> m_offsets;

		RocketCreator m_rocketCreator;

		void createRockets(Sequence& out);

	public:

		SequenceCreator()
		{
			for(int i=0; i<Settings::maxRocketsPerSequence(); ++i)
				m_nrRockets.push(i+1);

			m_intervals.push(0.0f);
			m_intervals.push(0.25f);
			m_intervals.push(0.5f);
			m_intervals.push(0.75f);
			m_intervals.push(1.0f);

			m_offsets.push(RocketBehaviour::POINT);
			m_offsets.push(RocketBehaviour::LINE);
			m_offsets.push(RocketBehaviour::CIRCLE);
		}

		void create(Sequence& out);

	};

};