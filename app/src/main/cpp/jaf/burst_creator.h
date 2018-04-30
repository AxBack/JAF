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
		};

		Release* m_pRelease = { nullptr };

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<Release> m_releases;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

		int rand(const Range<int>& range) { return JAWE::Random::randi(range.min, range.max); }

	public:

		BurstCreator();

		void step()
		{
			m_pRelease = m_releases.frontPtr();
		}

		virtual BurstBehaviour* create() override;
	};

};