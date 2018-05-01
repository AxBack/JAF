#pragma once

#include <atomic>

namespace JAF {

	class Settings
	{
	public:
		static bool allowTimeDeviation() { return true; }
		static bool allowPositionDeviation() { return true; }
		static bool allowBurstDeviation() { return true; }
		static bool allowTrailDeviation() { return false; }
	};
};