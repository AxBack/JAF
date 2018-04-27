#pragma once

#include "behaviour.h"

namespace JAF {

	class RocketBehaviour : public PathBehaviour
	{
	private:

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;

	public:

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

		virtual void fire(Particle* pParticle) override
		{

		}

		virtual void normalize() override
		{
			PathBehaviour::normalize(m_positions);
		}

		virtual bool update(BehaviourInfluenced* pItem, float time) override
		{
			if(time >= m_timeLimit)
				return false;

			float delta = time / m_timeLimit;

			pItem->setPosition(PathBehaviour::update<Math::Vector3>({0,0,0}, m_positions, delta));
			pItem->setRadius(0);

			return true;
		}
	};
};