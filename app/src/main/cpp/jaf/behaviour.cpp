#include "behaviour.h"

#include <random>

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

        Math::Vector3 pos;
        float size = 0;
        Math::Color color;

        {
            const int_float_vec *p = pItem->getPositionWeights();
            for(auto& it : *p)
                pos += m_positions[it.first].second->traverse(time) * it.second;
        }

        {
            const int_float_vec *p = pItem->getSizeWeights();
            for(auto& it : *p)
                size += m_sizes[it.first].second->traverse(time) * it.second;
        }

        {
            const int_float_vec *p = pItem->getColorWeights();
            for(auto& it : *p)
                color += m_colors[it.first].second->traverse(time) * it.second;
        }


        pItem->setPosition( pos );
        pItem->setSize( size );
        pItem->setColor( color );

        return true;
    }
}

