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

		struct Offsets
		{
			BalancedCollection<int> rotations;
			std::vector<Math::Matrix> transforms;
		};

		class ParticleCreator : public BurstCreator
		{
		public:
			virtual void init() override;
			//virtual BurstBehaviour* create() override;
		};

		Range<float> m_timeRange { 0.3f, 0.6f };
		Range<float> m_intervalRange { 0.005f, 0.025f };

		std::vector<vec3_path_ptr> m_rotations;
		BalancedCollection<Offsets> m_offsets;
		BalancedCollection<UINT> m_nrParticlesPerBurst;

		ParticleCreator m_particleCreator;

	public:

		SlowBurstCreator();

		virtual SlowBurstBehaviour* create();
	};
}