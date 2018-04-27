#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "burst_creator.h"

namespace JAF {

	class RocketCreator : public PathBehaviourCreator
	{
	private:

		typedef Math::Vector3 Vector3;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		BalancedCollection<vec3_path_ptr> m_positions;

	public:
		RocketCreator()
		: PathBehaviourCreator(2)
		{
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {-300,500,0}, {300,1250,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {300,500,0}, {-300,1250,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,-300}, {0,1250,300}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,300}, {0,1250,-300}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,600}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,-600}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {600,1000,0}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {-600,1000,0}, {0,1500,0}}));
		}

		virtual behaviour_ptr create() override
		{
			behaviour_ptr p = get();
			p->init(2.0f);
			fill(p.get(), JAWE::Random::randi(1,3), &m_positions);

			p->normalize();

			return p;
		}

	};

};