#pragma once

#include "balanced_collection.h"
#include "../jawe/vector3.h"
#include "creator.h"
#include "burst_creator.h"
#include "rocket_behaviour.h"
#include "trail_creator.h"

namespace JAF {

	class RocketCreator : public PathBehaviourCreator<RocketBehaviour>
	{
	private:

		typedef Math::Vector3 Vector3;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		BalancedCollection<vec3_path_ptr> m_positions;

		BurstCreator m_burstCreator;
		TrailCreator m_trailCreator;

	public:
		RocketCreator()
		: PathBehaviourCreator(2)
		{
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {-300,500,0}, {300,1250,0}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {300,500,0}, {-300,1250,0}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,-300}, {0,1250,300}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,300}, {0,1250,-300}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,600}, {0,1500,0}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,-600}, {0,1500,0}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {600,1000,0}, {0,1500,0}}));
			m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {-600,1000,0}, {0,1500,0}}));

			m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {0,1500,-250}}));
			m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {0,1500,250}}));
			m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {-250,1500,0}}));
			m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {250,1500,0}}));

			m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {0,400,500}, {500,800,0}, {0,1200,-200}}));
			m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {0,400,-500}, {-500,800,0}, {0,1200,200}}));
			m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {-500,400,0}, {0,800,500}, {200,1200,0}}));
			m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {500,400,0}, {0,800,-500}, {-200,1200,0}}));
		}

		virtual RocketBehaviour* create() override
		{
			RocketBehaviour* p = getBehaviour();
			p->init(JAWE::Random::randf(2.0f, 3.0f));
			fill(p, JAWE::Random::randi(1,2), &m_positions);
			p->normalize();

			p->add(m_burstCreator.create());
			p->add(0.025f, m_trailCreator.create());

			return p;
		}

	};

};