#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "burst_behaviour.h"

namespace JAF {

	class BurstCreator : public PathBehaviourCreator<BurstBehaviour>
	{
	private:

		template <typename T> struct Range { T min, max; };

		struct Release
		{
			Range<int> positionRange;
			Range<int> sizeRange;
			Range<int> colorRange;
			Range<float> forcedWeight;
			std::vector<vec3_path_ptr> forced;
			BalancedCollection<float> degrees;

			BalancedCollection<float> interval;
			BalancedCollection<int> nrPerSubBurst;
		};

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<Release> m_releases;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

		BalancedCollection<vec3_path_ptr> m_releasePaths;
		BalancedCollection<UINT> m_nrBursts;
		BalancedCollection<UINT> m_nrParticles;

		BalancedCollection<float> m_timeDeviation;
		BalancedCollection<float> m_positionDeviation;
		BalancedCollection<float> m_sizeDeviation;
		BalancedCollection<float> m_colorDeviation;

		int rand(const Range<int>& range) { return JAWE::Random::randi(range.min, range.max); }

		Behaviour* from(Release* pRelease);

	public:

		BurstCreator();

		virtual BurstBehaviour* create() override;
	};

};