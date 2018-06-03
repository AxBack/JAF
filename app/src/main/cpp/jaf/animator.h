#pragma once

#include "../jawe/counter.h"
#include "../jawe/path.h"

namespace JAF {

	class Animator
	{
	private:

		JAWE::Counter m_counter;
		JAWE::Path<float> m_path;

	public:

		void init(float min, float max)
		{
			float p[] { min, max};
			m_path.clear();
			m_path.add(1.0f, 2, p);
		};

		float advance()
		{
			return m_path.traverse(m_counter.time());
		}

		void start()
		{
			m_counter = JAWE::Counter();
		}

	};
};