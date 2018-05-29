#pragma once

#include "../jawe/gfx/instance_collector.h"

namespace JAF {

	class Updater;
	struct ParticleInstance;

	struct UpdateData
	{
		Updater* pUpdater;
		JAWE::GFX::InstanceCollector<ParticleInstance>* pInstanceCollector;
		float dt;
	};
};

#include "updater.h"
