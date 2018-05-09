#pragma once

#include "../jawe/counter.h"
#include "../jawe/path.h"

namespace JAF {

	class Animator
	{
	private:

		JAWE::Counter m_counter;

		float m_time {0};
		float m_value {0};

		bool m_running { false };

		JAWE::Path<float> m_path;

	public:

		float advance()
		{
			m_time += m_counter.step();
			m_value = m_path.traverse(m_time);
			if(m_time >= m_path.getLength())
			{
				m_time = 0;
				m_path.clear();
			}

			return m_value;
		}

		bool isRunning() const { return m_running; }

		void start()
		{
			if(m_running)
				return;

			m_counter.step();
			m_value = m_value >= 360 ? m_value-360 : m_value;
			float p[3] = {m_value, m_value+90, m_value+90 };
			m_path.add(2.0f, 3, p);
		}

	};
};