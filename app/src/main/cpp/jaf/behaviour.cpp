#include "behaviour.h"

namespace JAF {

    void Behaviour::fire(BehaviourInfluenced *pItem) const
    {
        //temp
        {
            int_float_vec w;
            w.push_back(std::make_pair(0, 1));
            pItem->setPositionWeights(std::move(w));
        }
        {
            int_float_vec w;
            w.push_back(std::make_pair(0, 1));
            pItem->setSizeWeights(std::move(w));
        }
        {
            int_float_vec w;
            w.push_back(std::make_pair(0, 1));
            pItem->setColornWeights(std::move(w));
        }
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

