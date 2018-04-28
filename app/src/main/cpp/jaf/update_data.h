#pragma once

#include "../jawe/instance_collector.h"

namespace JAF {

	class Updater;
	struct ParticleInstance;

	struct UpdateData
	{
		Updater* pUpdater;
		InstanceCollector<ParticleInstance>* pInstanceCollector;
		float dt;
	};
};

#include "updater.h"
