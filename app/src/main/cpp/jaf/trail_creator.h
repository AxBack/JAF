#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "trail_behaviour.h"

namespace JAF {

	class TrailCreator : public PathBehaviourCreator<TrailBehaviour>
	{
	private:

		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

	public:

		TrailCreator()
				: PathBehaviourCreator(10)
		{
			m_sizes.push(createPath(4, (float[]){1,3,1,0}));
			m_sizes.push(createPath(4, (float[]){1,2,2,0}));

			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,0,1}, {1,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,0,1}, {0,1,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,0,1,1}, {0,0,1,0}}));
		}

		virtual TrailBehaviour* create() override
		{
			TrailBehaviour* p = getBehaviour();
			p->init(0.4f);
			fill(p, JAWE::Random::randi(1,2), &m_sizes);
			fill(p, JAWE::Random::randi(1,2), &m_colors);

			p->normalize();

			return p;
		}

	};

};