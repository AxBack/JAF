#include "particle.h"

namespace JAF {

    void Particle::fire(ParticleListener* pListener, std::mt19937& generator, const Behaviour* pBehaviour)
    {
        m_time = 0;
		m_pListener = pListener;
        m_pBehaviour = pBehaviour;
		pBehaviour->fire(generator, this);
    }

    bool Particle::update(InstanceCollector<ParticleInstance>& collector, float dt)
    {
        m_time += dt;
        if(!m_pBehaviour->update(this, m_time))
        {
            if(m_pListener)
				m_pListener->onDead(this);
            return false;
        }

        if (m_instance.size > 0 && m_instance.a > 0)
            collector.add(m_instance);

        return true;
    }
}
