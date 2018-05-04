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

		struct Item
		{
			float value;
			float factor;
			T item;
		};

		float m_modifier;
		std::vector<Item> m_items;

	public:

		BalancedCollection(float modifier = 1.0f)
				: m_modifier(modifier)
		{}

		UINT size() { return (UINT)m_items.size(); }

		void push(T v, float factor = 1.0f) { m_items.push_back({ 0, factor, v}); }

		T front()
		{
			return *frontPtr();
		}

		T* frontPtr()
		{
			if(m_items.size() == 0)
				throw std::length_error("No items");
			else if(m_items.size() == 1)
				return &m_items[0].item;

			UINT index = 0;
			for(UINT i=1; i<m_items.size(); ++i)
			{
				if(m_items[i].value > m_items[index].value
				   || (m_items[i].value == m_items[index].value && JAWE::Random::randb()) )
				{
					m_items[index].value += m_modifier;
					index = i;
				}
				else
					m_items[i].value += m_modifier;
			}

			m_items[index].value -= m_modifier * m_items[index].factor;
			return &m_items[index].item;
		}

	};

};