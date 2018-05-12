#pragma once

#include <chrono>

namespace JAWE {

	class Counter
	{
	private:

		typedef std::chrono::steady_clock clock;
		typedef std::chrono::steady_clock::time_point time_point;

		time_point m_now = clock::now();
		time_point m_last = clock::now();

	public:

		float step()
		{
			m_last = m_now;
			m_now = clock::now();
			std::chrono::duration<float> dt = m_now - m_last;
			return dt.count();
		}

		float time() const
		{
			auto now = clock::now();
			std::chrono::duration<float> dt = now - m_last;
			return dt.count();
		}
	};
};