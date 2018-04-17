#include "rocket.h"

namespace JAF {

    void Rocket::fire(float life, const vec3_path* pPosition, const float_path* pSize,
                      const color_path* pColor)
    {
        m_life = 0;
        m_lifeSpan = life;
        m_pPosition = pPosition;
        m_pSize = pSize;
        m_pColor = pColor;
    }

    bool Rocket::update(InstanceCollector<ParticleInstance>& collector, float dt)
    {
        m_life += dt;
        if (m_life >= m_lifeSpan)
            return false;

        Math::Vector3 pos = m_pPosition->traverse(m_life);
        m_instance.size = m_pSize->traverse(m_life);
        Math::Color color = m_pColor->traverse(m_life);

        m_instance.x = pos.x();
        m_instance.y = pos.y();
        m_instance.z = pos.z();
        m_instance.a = color.a();
        m_instance.r = color.r();
        m_instance.g = color.g();
        m_instance.b = color.b();

        collector.add(m_instance);
        return true;
    }
}
