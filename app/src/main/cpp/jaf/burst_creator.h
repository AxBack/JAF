#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"

namespace JAF {

	class BurstCreator : public Creator
	{
	private:

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

	public:



		BurstCreator()
				: Creator(5)
		{
			m_positions.push(createPath(1.0f, 2, (Vector3[]){{0,0,0}, {0,500,0}}));
			m_positions.push(createPath(1.0f, 2, (Vector3[]){{0,0,0}, {0,300,0}}));

			m_sizes.push(createPath(1.0f, 4, (float[]){0.1,1,1,0} ));
			m_sizes.push(createPath(1.0f, 4, (float[]){1,2,0.1,0}));

			m_colors.push(createPath(1.0f, 3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
			m_colors.push(createPath(1.0f, 3, (Color[]){{1,0,0,1}, {1,0,0,1}, {1,0,0,0}}));
			m_colors.push(createPath(1.0f, 3, (Color[]){{0,1,0,1}, {0,1,0,1}, {0,1,0,0}}));
			m_colors.push(createPath(1.0f, 4, (Color[]){{0,0,1,1}, {0,0,1,1}, {0,0,1,0}}));
		}

		virtual behaviour_ptr create() override
		{
			behaviour_ptr p = getBehaviour();
			p->init(2.0f);
			fill(p.get(), JAWE::Random::rand(1,2), &m_positions);
			fill(p.get(), JAWE::Random::rand(1,2), &m_sizes);
			fill(p.get(), JAWE::Random::rand(1,2), &m_colors);

			p->normalize();

			return p;
		}

	};

};