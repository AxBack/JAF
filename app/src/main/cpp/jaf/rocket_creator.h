#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "rocket_behaviour.h"
#include "trail_creator.h"
#include "settings.h"
#include "slow_burst_creator.h"

namespace JAF {

	class RocketCreator : public PathBehaviourCreator<RocketBehaviour>
	{
	private:

		typedef Math::Vector3 Vector3;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;
		typedef std::function<void(RocketBehaviour*)> behaviour_func;

		BalancedCollection<float> m_timeDeviation;
		BalancedCollection<float> m_positionDeviation;

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<UINT> m_nrBursts;
		BalancedCollection<UINT> m_nrParticles;

		BalancedCollection<behaviour_func> m_creators;

		BurstCreator m_burstCreator;
		SlowBurstCreator m_slowBurstCreator;
		TrailCreator m_trailCreator;

	public:

		RocketCreator();

		virtual RocketBehaviour* create() override;

		virtual void step() override
		{

		}

	};

};