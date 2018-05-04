#pragma once

#include <set>
#include <atomic>
#include "../pch.h"

namespace JAF {

	class Settings
	{
	private:

		static std::atomic_bool m_allowDeviation;
		static std::atomic_bool m_allowTimeDeviation;
		static std::atomic_bool m_allowPositionDeviation;
		static std::atomic_bool m_allowBurstDeviation;
		static std::atomic_bool m_allowTrailDeviation;

	public:

		static bool allowTimeDeviation() { return m_allowDeviation && m_allowTimeDeviation; }
		static bool allowPositionDeviation() { return m_allowDeviation && m_allowPositionDeviation; }
		static bool allowBurstDeviation() { return m_allowDeviation && m_allowBurstDeviation; }
		static bool allowTrailDeviation()  { return m_allowDeviation && m_allowTrailDeviation; }
		static UINT nrBursts() { return 3; }
		static int minNrRockets() { return 1; }
		static int maxRocketsPerSequence() { return 8; }

		static void allowDeviation(bool allow) { m_allowDeviation = allow; }
	};
};