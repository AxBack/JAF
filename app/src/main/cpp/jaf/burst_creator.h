#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "burst_behaviour.h"

namespace JAF {

	class BurstCreator : public PathBehaviourCreator<BurstBehaviour>
	{
	private:

		typedef std::shared_ptr<BurstBehaviour> behaviour_ptr;

		BalancedCollection<vec3_path_ptr> m_positions;
		BalancedCollection<float_path_ptr> m_sizes;
		BalancedCollection<color_path_ptr> m_colors;

	public:



		BurstCreator()
				: PathBehaviourCreator(5)
		{
			m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,500,0}}));
			m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,300,0}}));

			m_sizes.push(createPath(4, (float[]){1,1,1,0} ));
			m_sizes.push(createPath(4, (float[]){1,5,1,0}));

			m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{1,0,0,1}, {1,0,0,1}, {1,0,0,0}}));
			m_colors.push(createPath(3, (Color[]){{0,1,0,1}, {0,1,0,1}, {0,1,0,0}}));
			m_colors.push(createPath(4, (Color[]){{0,0,1,1}, {0,0,1,1}, {0,0,1,0}}));
		}

		virtual behaviour_ptr create() override
		{
			behaviour_ptr p = get();
			p->init(2.0f);
			fill(p.get(), JAWE::Random::randi(1,2), &m_positions);
			fill(p.get(), JAWE::Random::randi(1,2), &m_sizes);
			fill(p.get(), JAWE::Random::randi(1,2), &m_colors);

			p->normalize();

			return p;
		}

	};

};