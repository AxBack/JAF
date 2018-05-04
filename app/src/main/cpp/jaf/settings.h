#pragma once

#include <atomic>

namespace JAF {

	class Settings
	{
	public:
		static bool allowTimeDeviation() { return true; }
		static bool allowPositionDeviation() { return true; }
		static bool allowBurstDeviation() { return true; }
		static bool allowTrailDeviation()  { return false; }
		static UINT nrBursts() { return 3; }
		static int minNrRockets() { return 1; }
		static int maxRocketsPerSequence() { return 8; }
	};
};