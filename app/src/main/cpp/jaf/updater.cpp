#include "updater.h"

namespace JAF {

    bool Updater::init()
    {
		m_director.init(m_generator);

        return JAWE::Updater::init();
    }

    void Updater::fireParticle(ParticleListener* pListener, const Behaviour *pBehaviour,
                               matrix_ptr pOffset, int type, const Math::Vector3& factors)
    {
        particle_ptr p = m_particleBank.pop();
		p->clear();
        p->setType(type);
		p->setOffset(pOffset);
		p->setFactors(factors);
        p->fire(pListener, m_generator, pBehaviour);
        m_particlesToAdd.push_back(p);
    }

    void Updater::advance(float dt)
    {
        m_particleCollector.begin();
        for(auto it = m_particles.begin(); it != m_particles.end();)
        {
            if(!(*it)->update(m_particleCollector, dt))
            {
                m_particleBank.push(*it);
                it = m_particles.erase(it);
            }
            else
                ++it;
        }

        {
            std::lock_guard<std::mutex> _(m_particleMutex);
            m_particleCollector.end(m_particlesInstances);
        }

        for(auto& it : m_particlesToAdd)
            m_particles.push_back(it);
        m_particlesToAdd.clear();

        m_director.update(this, dt);
    }

    void Updater::updateInstances(particle_mesh& mesh)
    {
        std::lock_guard<std::mutex> _(m_particleMutex);
        mesh.updateInstances(m_particlesInstances.size(), m_particlesInstances.size() == 0 ? nullptr : &m_particlesInstances[0]);
    }
}
