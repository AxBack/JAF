#include "particle.h"

namespace JAF {

    void Particle::fire(const Behaviour* pBehaviour)
    {
        m_time = 0;
        m_pBehaviour = pBehaviour;
    }

    bool Particle::update(InstanceCollector<ParticleInstance>& collector, float dt)
    {
        m_time += dt;
        if(!m_pBehaviour->update(this, m_time))
            return false;

        if (m_instance.size > 0 && m_instance.a > 0)
            collector.add(m_instance);
        return true;
    }
}
