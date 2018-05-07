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

		struct Release
		{
			Math::Vector3 rot;
			Range<float> weight;
			vec3_path_ptr pForced;
		};

		Range<int> m_positionRange {1, 2};
		Range<int> m_sizeRange {1, 2};
		Range<int> m_colorRange {1, 2};

		BalancedCollection<Vector3> m_gravity;

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

		BalancedCollection<Release> m_releaseRotation;

		BalancedCollection<bool> m_deviation;
		BalancedCollection<float> m_timeDeviation;
		BalancedCollection<float> m_positionDeviation;
		BalancedCollection<float> m_sizeDeviation;
		BalancedCollection<float> m_colorDeviation;

		Release* m_pCurrentRelease;
		bool m_deviate { false };

		int rand(const Range<int>& range) { return JAWE::Random::randi(range.min, range.max); }
		float rand(const Range<float>& range) { return JAWE::Random::randf(range.min, range.max); }

		Release createRelease(const Math::Vector3& rot, const Range<float>& range, UINT nrPoints, Vector3* pPoints)
		{
			Release r { rot, range };
			if(nrPoints > 0)
				r.pForced = createPath(nrPoints, pPoints);

			return std::move(r);
		};

	public:

		BurstCreator();

		virtual BurstBehaviour* create() override;

		virtual void step() override
		{
			m_pCurrentRelease = m_releaseRotation.frontPtr();
			m_deviate = Settings::allowRocketDeviation() && m_deviation.front();
		}
	};

};