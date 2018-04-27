#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "trail_behaviour.h"

namespace JAF {

	class TrailCreator : public PathBehaviourCreator<TrailBehaviour>
	{
	private:

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

	public:

		TrailCreator()
				: PathBehaviourCreator(10)
		{
			float l = 100.0f;
			m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {-l,0,-l}}));
			m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {l,0,l}}));

			m_sizes.push(createPath(4, (float[]){1,3,1,0}));
			m_sizes.push(createPath(4, (float[]){1,2,2,0}));

			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,0,0,1}, {1,0,0,1}, {1,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{0,1,0,1}, {0,1,0,1}, {0,1,0,0}}));
			m_colors.push(createPath(4, (Color[]){{0,0,1,1}, {0,0,1,1}, {0,0,1,0}}));
		}

		virtual TrailBehaviour* create() override
		{
			TrailBehaviour* p = getBehaviour();
			p->init(0.2f);
			fill(p, JAWE::Random::randi(2,3), &m_positions);
			fill(p, JAWE::Random::randi(1,2), &m_sizes);
			fill(p, JAWE::Random::randi(1,2), &m_colors);

			p->normalize();

			return p;
		}

	};

};