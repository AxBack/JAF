#pragma once

#include "../jawe/color.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "behaviour.h"
#include "sequence.h"
#include "sequence_creator.h"

namespace JAF {

	class Updater;

	class Director
	{
	private:

		typedef JAWE::Path<Math::Vector3> vec3_path;
		typedef std::vector<vec3_path> vec3_path_vec;
		typedef JAWE::Path<float> float_path;
		typedef std::vector<float_path> float_path_vec;
		typedef JAWE::Path<Math::Color> color_path;
		typedef std::vector<color_path> color_path_vec;
		typedef std::vector<Behaviour> behaviour_vec;
		typedef std::shared_ptr<Sequence> sequence_ptr;

		std::mt19937 m_generator;

		struct Settings
		{
			vec3_path_vec vec3Paths;
			float_path_vec floatPaths;
			color_path_vec colorPaths;
		};

		Settings m_trailSettings;

		behaviour_vec m_trailBehaviours;

		SequenceCreator m_creator;

		sequence_ptr m_pSequence;

		template<typename T>
		JAWE::Path<T> createPath(float time, UINT nrPoints, T* p)
		{
			JAWE::Path<T> path;
			path.add(time, nrPoints, p);
			return path;
		}

	public:

		void init(std::mt19937& generator);

		void update(Updater* pUpdater, float dt);
	};
};