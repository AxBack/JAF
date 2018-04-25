#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"

namespace JAF {

	class RocketCreator
	{
	private:

		typedef Math::Vector3 Vector3;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		BalancedCollection<vec3_path_ptr> m_positions;

		vec3_path_ptr createPath(float time, UINT nrPoints, Vector3* p)
		{
			vec3_path_ptr pPath(new vec3_path());
			pPath->add(time, nrPoints, p);
			return pPath;
		}

	public:
		RocketCreator()
		{
			m_positions.push(createPath(1.0f, 2, (Math::Vector3[]){{0,0,0}, {-300,600,-300}}));
			m_positions.push(createPath(1.0f, 2, (Math::Vector3[]){{0,0,0}, {300,600,300}}));
		}

		void create(Behaviour& out)
		{
			for(UINT t=0; t<2; ++t)
				out.addPosition(JAWE::Random::rand(1.0f, 5.0f), m_positions.front().get());

		}

	};

};