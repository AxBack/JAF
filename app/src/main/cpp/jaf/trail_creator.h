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
			m_sizes.push(createPath(3, (float[]){4,5,0}));
			m_sizes.push(createPath(3, (float[]){3,2,0}));
			m_sizes.push(createPath(3, (float[]){5,8,0}));
			m_sizes.push(createPath(3, (float[]){10,7,0}));

			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,0,1}, {1,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,0,1}, {0,1,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,0,1,1}, {0,0,1,0}}));
		}

		virtual TrailBehaviour* create() override
		{
			TrailBehaviour* p = getBehaviour();
			p->init(JAWE::Random::randf(0.3f, 0.6f));
			fill(p, JAWE::Random::randi(1,2), &m_sizes);
			fill(p, JAWE::Random::randi(1,2), &m_colors);
			p->setDispersion(JAWE::Random::randf(2.0, 3.0f));
			p->setGravity({0, -JAWE::Random::randf(10, 500), 0});

			p->normalize();

			return p;
		}

	};

};