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

		JAWE::Path<float> m_path;

	public:

		float advance()
		{
			m_time += m_counter.step();

			if(m_path.getLength() == 0)
			{
				if(m_time >= 10.0f)
				{
					m_value = m_value >= 360 ? m_value-360 : m_value;
					float p[3] = {m_value, m_value+90, m_value+90 };
					m_path.add(3.0f, 3, p);
					m_time = 0.0f;
				}
			}
			else
			{
				m_value = m_path.traverse(m_time);
				if(m_time >= m_path.getLength())
				{
					m_time = 0;
					m_path.clear();
				}
			}

			return m_value;
		}

		void resume()
		{
			m_counter.step();
		}

		void pause()
		{
		}

	};
};