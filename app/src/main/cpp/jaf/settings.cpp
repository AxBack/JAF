#include "settings.h"

namespace JAF {

	std::atomic_bool Settings::m_allowDeviation(true);
	std::atomic_bool Settings::m_allowTimeDeviation(true);
	std::atomic_bool Settings::m_allowPositionDeviation(true);
	std::atomic_bool Settings::m_allowBurstDeviation(true);
	std::atomic_bool Settings::m_allowTrailDeviation(true);

}