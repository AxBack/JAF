#pragma once

#include <set>
#include <atomic>
#include "../pch.h"

namespace JAF {

	class Settings
	{
	private:

		static std::atomic_bool s_allowRocketDeviation;
		static std::atomic_bool s_allowBurstDeviation;
		static std::atomic_bool s_allowTrailDeviation;
		static std::atomic_int s_nrBursts;
		static std::atomic_int s_minNrRockets;
		static std::atomic_int s_maxNrRocketsPerSequence;

	public:

		static bool allowRocketDeviation() { return s_allowRocketDeviation; }
		static bool allowBurstDeviation() { return s_allowBurstDeviation; }
		static bool allowTrailDeviation()  { return s_allowTrailDeviation; }
		static UINT nrBursts() { return s_nrBursts; }
		static int minNrRockets() { return s_minNrRockets; }
		static int maxRocketsPerSequence() { return s_maxNrRocketsPerSequence; }

		static void allowRocketDeviation(bool allow) { s_allowRocketDeviation = allow; }
		static void allowBurstDeviation(bool allow) { s_allowBurstDeviation = allow; }
		static void allowTrailDeviation(bool allow) { s_allowTrailDeviation = allow; }

		static void nrBursts(int nr) { s_nrBursts = nr; }
		static void minNrRockets(int nr) { s_minNrRockets = nr; }
		static void maxNrRocketsPerSequence(int nr) { s_maxNrRocketsPerSequence = nr; }
	};
};