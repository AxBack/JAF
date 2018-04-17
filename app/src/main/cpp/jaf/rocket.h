#pragma once

#include "../jawe/vector3.h"
#include "instance_collector.h"
#include "vertex.h"
#include "../jawe/path.h"
#include "../jawe/color.h"

namespace JAF {

    class Rocket
    {
    private:

        typedef JAWE::Path<Math::Vector3> vec3_path;
        typedef JAWE::Path<float> float_path;
        typedef JAWE::Path<Math::Color> color_path;

        float m_life;
        float m_lifeSpan;
        ParticleInstance m_instance;

        const vec3_path* m_pPosition;
        const float_path* m_pSize;
        const color_path* m_pColor;

    public:

        void fire(float life, const vec3_path* pPosition, const float_path* pSize, const color_path* pColor);

        bool update(InstanceCollector<ParticleInstance>& collector, float dt);

    };
}