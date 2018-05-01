#pragma once

#include <vector>

#include "../jawe/path.h"

namespace JAF {

	template <typename T>
	class WeightedValue
	{
	private:

		std::vector<float> m_weights;
		std::vector<JAWE::Path<T>*> m_values;

		float m_total = 0.0f;

		void normalize(std::vector<float>& v, float total) const
		{
			for(auto& it : v)
				it = it / m_total;
		}

	public:

		void clear()
		{
			m_weights.clear();
			m_values.clear();
			m_total = 0.0f;
		}

		std::vector<float> deviate(float d) const
		{
			if(d <= 0.0f)
				return m_weights;

			std::vector<float> v = m_weights;
			float total = 0.0f;
			for(auto& it : v)
			{
				it += JAWE::Random::randf(-d, d);
				total += it;
			}

			normalize(v, total);
			return std::move(v);
		}

		void add(float weight, JAWE::Path<T>* pValue)
		{
			m_total += weight;
			m_weights.push_back(weight);
			m_values.push_back(pValue);
		}

		void normalize()
		{
			normalize(m_weights, m_total);
			m_total = 1.0f;
		}

		T update(T v, float time)
		{
			for(UINT i=0; i<m_values.size(); ++i)
			{
				v += m_values[i]->traverse(time) * m_weights[i];
				++i;
			}
			return v;
		}

		T update(T v, const std::vector<float>& w, float time)
		{
			for(UINT i=0; i<w.size(); ++i)
			{
				v += m_values[i]->traverse(time) * w[i];
			}
			return v;
		}
	};
};