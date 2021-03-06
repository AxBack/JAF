#pragma once

#include <atomic>
#include "balanced_collection.h"
#include "../jawe/math/vector3.h"
#include "creator.h"
#include "burst_behaviour.h"
#include "settings.h"

namespace JAF {

	class BurstCreator : public PathBehaviourCreator<BurstBehaviour>
	{
	protected:

		struct Release
		{
			JAWE::MATH::Vector3 rot;
			JAWE::Range<float> weight;
			vec3_path_ptr pForced;
		};

		JAWE::Range<float> m_lifeRange {1.5, 2.5f };
		JAWE::Range<int> m_positionRange {1, 2};
		JAWE::Range<int> m_sizeRange {1, 2};
		JAWE::Range<int> m_colorRange {1, 2};

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

		Release createRelease(const JAWE::MATH::Vector3& rot, const JAWE::Range<float>& range, UINT nrPoints, Vector3* pPoints)
		{
			Release r { rot, range };
			if(nrPoints > 0)
				r.pForced = createPath(nrPoints, pPoints);

			return std::move(r);
		}

	public:

		BurstCreator();

		virtual void init();

		virtual BurstBehaviour* create() override;

		virtual void step() override
		{
			m_pCurrentRelease = m_releaseRotation.frontPtr();
			m_deviate = Settings::allowBurstDeviation() && m_deviation.front();
		}
	};
}