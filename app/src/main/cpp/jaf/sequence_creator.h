#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/math/vector3.h"
#include "sequence.h"
#include "rocket_creator.h"
#include "trail_creator.h"

namespace JAF {

	class SequenceCreator
	{
	private:

		struct Release
		{
			RocketBehaviour::OffsetType type;
			float tag;
		};

		BalancedCollection<int> m_nrRockets;
		BalancedCollection<float> m_intervals;
		BalancedCollection<Release> m_offsets;

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

			m_offsets.push({RocketBehaviour::POINT, 0});
			m_offsets.push({RocketBehaviour::LINE, 0});
			m_offsets.push({RocketBehaviour::CIRCLE, 360 });
			m_offsets.push({RocketBehaviour::CIRCLE, 180 });
			m_offsets.push({RocketBehaviour::CIRCLE, 90 });
		}

		void create(Sequence& out);

	};

};