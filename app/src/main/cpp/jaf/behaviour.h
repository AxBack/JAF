#pragma once

#include "../jawe/vector3.h"
#include "../jawe/color.h"
#include "../jawe/path.h"

namespace JAF {

    typedef JAWE::Path<Math::Vector3> vec3_path;
    typedef JAWE::Path<float> float_path;
    typedef JAWE::Path<Math::Color> color_path;

    class BehaviourInfluenced
    {
    public:

        virtual void setPosition(const Math::Vector3& position) = 0;
        virtual void setSize(const float size) = 0;
        virtual void setColor(const Math::Color& color) = 0;
    };

    class Behaviour
    {
        float m_timeLimit;

        const vec3_path* m_pPosition;
        const float_path* m_pSize;
        const color_path* m_pColor;

    public:

        Behaviour()
                : m_timeLimit(0)
        {}

        void init(float time, const vec3_path* pPosition, const float_path* pSize, const color_path* pColor)
        {
            m_timeLimit = time;
            m_pPosition = pPosition;
            m_pSize = pSize;
            m_pColor = pColor;
        }

        bool update(BehaviourInfluenced* pItem, float time) const
        {
            if (time >= m_timeLimit)
                return false;

            pItem->setPosition( m_pPosition->traverse(time) );
            pItem->setSize( m_pSize->traverse(time) );
            pItem->setColor( m_pColor->traverse(time) );

            return true;
        }
    };
}
