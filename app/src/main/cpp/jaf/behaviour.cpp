#include "behaviour.h"

namespace JAF {

    bool Behaviour::update(BehaviourInfluenced* pItem, float time) const
    {
        if (time >= m_timeLimit)
		{
			return false;
		}

        pItem->setPosition(update<Math::Vector3>({0,0,0}, m_positions, time));
		pItem->setRadius(update(0.0f, m_sizes, time));
        pItem->setColor(update<Math::Color>({0,0,0,0}, m_colors, time));

        return true;
    }
}

