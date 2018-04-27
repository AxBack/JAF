#pragma once

#include "behaviour.h"

namespace JAF {

	class BurstBehaviour : public PathBehaviour
	{
	private:

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;
		std::vector<std::pair<float, float_path_ptr>> m_sizes;
		std::vector<std::pair<float, color_path_ptr>> m_colors;

	public:

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

		void add(float weight, float_path_ptr pSize)
		{
			m_sizes.push_back(std::make_pair(weight, pSize));
		}

		void add(float weight, color_path_ptr pColor)
		{
			m_colors.push_back(std::make_pair(weight, pColor));
		}

		virtual void normalize() override
		{
			PathBehaviour::normalize(m_positions);
			PathBehaviour::normalize(m_sizes);
			PathBehaviour::normalize(m_colors);
		}

		virtual void fire(BehaviourInfluenced* pItem) override
		{
			PathBehaviour::fire(pItem);
		}

		virtual bool update(BehaviourInfluenced* pItem, float time) override
		{
			if(time >= m_timeLimit)
				return false;

			float delta = time / m_timeLimit;

			pItem->setPosition(PathBehaviour::update<Math::Vector3>({0,0,0}, m_positions, delta));
			pItem->setRadius(PathBehaviour::update<float>(0.0f, m_sizes, delta));
			pItem->setColor(PathBehaviour::update<Math::Color>({0,0,0,0}, m_colors, delta));

			return true;
		}
	};
};