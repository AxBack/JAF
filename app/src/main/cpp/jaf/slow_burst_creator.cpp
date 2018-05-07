#include "slow_burst_creator.h"

namespace JAF {

	SlowBurstCreator::SlowBurstCreator()
		: PathBehaviourCreator(5)
	{

	}

	SlowBurstBehaviour* SlowBurstCreator::create()
	{
		SlowBurstBehaviour* p = getBehaviour();
		p->init(1.0f);

		return p;
	}
}
