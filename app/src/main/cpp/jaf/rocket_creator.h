#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "../jawe/bank.h"

namespace JAF {

	class RocketCreator
	{
	private:

		typedef Math::Vector3 Vector3;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;
		typedef std::shared_ptr<Behaviour> behaviour_ptr;
		typedef JAWE::Bank<Behaviour> behaviour_bank;

		BalancedCollection<vec3_path_ptr> m_positions;

		behaviour_bank m_behaviourBank;

		vec3_path_ptr createPath(float time, UINT nrPoints, Vector3* p)
		{
			vec3_path_ptr pPath(new vec3_path());
			pPath->add(time, nrPoints, p);
			return pPath;
		}

	public:
		RocketCreator()
		: m_behaviourBank([](){return new Behaviour();})
		{
			for(UINT i=0; i<10; ++i)
				m_behaviourBank.push(m_behaviourBank.pop());

			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {-300,500,0}, {300,1250,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {300,500,0}, {-300,1250,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,-300}, {0,1250,300}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,300}, {0,1250,-300}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,600}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {0,1000,-600}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {600,1000,0}, {0,1500,0}}));
			m_positions.push(createPath(2.0f, 3, (Math::Vector3[]){{0,0,0}, {-600,1000,0}, {0,1500,0}}));
		}

		const Behaviour* create()
		{
			behaviour_ptr p = m_behaviourBank.pop();
			p->init(2.0f);
			int r = JAWE::Random::rand(1,3);
			for(int t=0; t<r; ++t)
				p->addPosition(JAWE::Random::rand(1.0f, 5.0f), m_positions.front().get());

			p->normalize();

			//temp
			m_behaviourBank.push(p);

			return p.get();
		}

	};

};