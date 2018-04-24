#pragma once

#include <random>

namespace JAWE {

	class Random
	{
	private:

		static std::mt19937 s_generator;

	public:

		static void seed(unsigned int seed) { s_generator = std::mt19937(seed); }

		static float rand(float min, float max)
		{
			std::uniform_real_distribution<float> dist(min, max);
			return dist(s_generator);
		}

	};
};