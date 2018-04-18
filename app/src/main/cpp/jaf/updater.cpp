#include "updater.h"

namespace JAF {

    bool Updater::init()
    {
        float time = 1.0f;
        {
            Math::Vector3 p[] {
                    {50,-100,-20},
                    {-50,100,2}
            };
            position.add(time, 2, p);
        }

        {
            Math::Color p[] {
                    {1,0,1,1},
                    {1,1,0,1}
            };
            color.add(time, 2, p);
        }

        {
            float p[] { 10,50,20,5};
            size.add(time, 4, p);
        }

        m_behaviour.init(time, &position, &size, &color);

        m_rocket.fire(&m_behaviour);
        return JAWE::Updater::init();
    }

    void Updater::advance(float dt)
    {
        m_particleCollector.begin();
        if(!m_rocket.update(m_particleCollector, dt))
        {
            m_rocket.fire(&m_behaviour);
        }

        {
            std::lock_guard<std::mutex> _(m_particleMutex);
            m_particleCollector.end(m_particles);
        }
    }

    void Updater::updateInstances(particle_mesh& mesh)
    {
        std::lock_guard<std::mutex> _(m_particleMutex);
        mesh.updateInstances(m_particles.size(), m_particles.size() == 0 ? nullptr : &m_particles[0]);
    }
}
