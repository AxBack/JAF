#include "updater.h"

namespace JAF {

    bool Updater::init()
    {
        {
            Math::Vector3 p[] {
                    {50,-100,10},
                    {-50,100,-10}
            };
            position.add(5.0f, 2, p);
        }

        {
            Math::Color p[] {
                    {1,0,1,1},
                    {1,1,0,1}
            };
            color.add(5.0f, 2, p);
        }

        {
            float p[] { 100,50,20,50};
            size.add(5.0f, 4, p);
        }

        m_rocket.fire(5.0f, &position, &size, &color);
        return JAWE::Updater::init();
    }

    void Updater::advance(float dt)
    {
        m_particleCollector.begin();
        if(!m_rocket.update(m_particleCollector, dt))
        {
            m_rocket.fire(5.0f, &position, &size, &color);
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
