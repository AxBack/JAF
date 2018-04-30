#pragma once

#include <utility>
#include <vector>
#include "../pch.h"
#include "behaviour.h"
#include <stdexcept>

namespace JAF {

	template <typename T>
	class BalancedCollection
	{
	private:

		float m_modifier;
		std::vector<std::pair<float, T>> m_items;

	public:

		BalancedCollection(float modifier = 1.0f)
				: m_modifier(modifier)
		{}

		UINT size() { return (UINT)m_items.size(); }

		void push(T v) { m_items.push_back(std::make_pair(0.0f, v)); }

		T front()
		{
			if(m_items.size() == 0)
				throw std::length_error("No items");
			else if(m_items.size() == 1)
				return m_items[0].second;

			UINT index = 0;
			for(UINT i=1; i<m_items.size(); ++i)
			{
				if(m_items[i].first > m_items[index].first
				   || (m_items[i].first == m_items[index].first && JAWE::Random::randb()) )
				{
					m_items[index].first += m_modifier;
					index = i;
				}
				else
					m_items[i].first += m_modifier;
			}

			m_items[index].first -= m_modifier;
			return m_items[index].second;
		}

	};

};