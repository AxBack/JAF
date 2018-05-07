#pragma once

#include "creator.h"
#include "slow_burst_behaviour.h"
#include "burst_creator.h"

namespace JAF {

	class SlowBurstCreator : public PathBehaviourCreator<SlowBurstBehaviour>
	{
	private:

		class ParticleCreator : public BurstCreator
		{
		public:
			virtual void init() override;
			//virtual BurstBehaviour* create() override;
		};

		Range<float> m_timeRange { 0.5f, 1.0f };

		ParticleCreator m_particleCreator;

	public:

		SlowBurstCreator();

		virtual SlowBurstBehaviour* create();
	};
}