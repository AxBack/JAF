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

		static float randf()
		{
			static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
			return dist(s_generator);
		}

		static float randf(float min, float max)
		{
			return min + (randf() * (max - min));
		}

		static int randi(int min, int max)
		{
			std::lock_guard<std::mutex> _(s_mutex);
			std::uniform_int_distribution<int> dist(min, max);
			return dist(s_generator);
		}

		static int randb()
		{
			static std::uniform_int_distribution<int> dist(0, 1);
			return dist(s_generator) == 1;
		}

	};
};