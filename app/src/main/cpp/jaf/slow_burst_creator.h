#pragma once

#include "creator.h"
#include "slow_burst_behaviour.h"

namespace JAF {

	class SlowBurstCreator : public PathBehaviourCreator<SlowBurstBehaviour>
	{
	private:

	public:

		SlowBurstCreator();

		virtual SlowBurstBehaviour* create();
	};
}