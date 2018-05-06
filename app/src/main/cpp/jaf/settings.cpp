#include "settings.h"

namespace JAF {

	std::atomic_bool Settings::s_allowRocketDeviation(true);
	std::atomic_bool Settings::s_allowBurstDeviation(true);
	std::atomic_bool Settings::s_allowTrailDeviation(true);
	std::atomic_int Settings::s_nrBursts(3);
	std::atomic_int Settings::s_minNrRockets(1);
	std::atomic_int Settings::s_maxNrRocketsPerSequence(5);

}