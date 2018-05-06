#pragma once

#include <atomic>
#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "burst_behaviour.h"
#include "settings.h"

namespace JAF {

	class BurstCreator : public PathBehaviourCreator<BurstBehaviour>
	{
	private:

		template <typename T> struct Range { T min, max; };

		Range<int> m_positionRange {1, 2};
		Range<int> m_sizeRange {1, 2};
		Range<int> m_colorRange {1, 2};

		BalancedCollection<Vector3> m_gravity;

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

		BalancedCollection<float> m_timeDeviation;
		BalancedCollection<float> m_positionDeviation;
		BalancedCollection<float> m_sizeDeviation;
		BalancedCollection<float> m_colorDeviation;

		int rand(const Range<int>& range) { return JAWE::Random::randi(range.min, range.max); }

	public:

		BurstCreator();

		virtual BurstBehaviour* create() override;
	};

};