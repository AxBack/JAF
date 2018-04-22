#include "behaviour.h"

namespace JAF {

	/** BEHAVIOUR **/
    void Behaviour::fire(std::mt19937& generator, BehaviourInfluenced *pItem) const
    {
		pItem->setPositionWeights(createDistribution(generator, m_positions));
		pItem->setSizeWeights(createDistribution(generator, m_sizes));
		pItem->setColorWeights(createDistribution(generator, m_colors));
    }

    bool Behaviour::update(BehaviourInfluenced* pItem, float time) const
    {
        if (time >= m_timeLimit)
            return false;

        pItem->setPosition(update<Math::Vector3>({0,0,0}, pItem->getPositionWeights(), m_positions, time));
        pItem->setSize(update(0.0f, pItem->getSizeWeights(), m_sizes, time));
        pItem->setColor(update<Math::Color>({0,0,0,0}, pItem->getColorWeights(), m_colors, time));

        return true;
    }
}

