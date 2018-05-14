#pragma once

#include "creator.h"
#include "slow_burst_behaviour.h"
#include "burst_creator.h"

namespace JAF {

	class SlowBurstCreator : public PathBehaviourCreator<SlowBurstBehaviour>
	{
	private:

		typedef JAWE::Path<Math::Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		class ParticleCreator : public BurstCreator
		{
		public:
			virtual void init() override;
			//virtual BurstBehaviour* create() override;
		};

		Range<float> m_timeRange { 0.2f, 0.5f };
		Range<float> m_intervalRange { 0.001f, 0.01f };

		BalancedCollection<vec3_path_ptr> m_rotations;
		BalancedCollection<UINT> m_nrPerCircleStep;
		BalancedCollection<UINT> m_nrParticlesPerBurst;

		ParticleCreator m_particleCreator;

	public:

		SlowBurstCreator();

		virtual SlowBurstBehaviour* create();
	};
}