#pragma once

#include <random>
#include <mutex>

namespace JAWE {

	class Random
	{
	private:

		static std::mt19937 s_generator;
		static std::mutex s_mutex;


	public:

		static void seed(unsigned int seed) { s_generator = std::mt19937(seed); }

		static float rand(float min, float max)
		{
			std::lock_guard<std::mutex> _(s_mutex);
			std::uniform_real_distribution<float> dist(min, max);
			return dist(s_generator);
		}

	};
};