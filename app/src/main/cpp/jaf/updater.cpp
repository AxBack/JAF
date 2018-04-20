#include "updater.h"

namespace JAF {

    bool Updater::init()
    {
        float time = 1.0f;
        m_behaviour.init(time);
        {
            Math::Vector3 p[] {
                    {0,-100,0},
                    {-50,100,-50}
            };
            position1.add(time, 2, p);
            m_behaviour.addPosition(1.0f, &position1);
        }
        {
            Math::Vector3 p[] {
                    {0,-100,0},
                    {50,100,50}
            };
            position2.add(time, 2, p);
            m_behaviour.addPosition(1.0f, &position2);
        }

        {
            Math::Color p[] {
                    {1,0,1,1},
                    {1,1,0,1}
            };
            color1.add(time, 2, p);
            m_behaviour.addColor(1.0f, &color1);
        }
        {
            Math::Color p[] {
                    {0,0,1,1},
                    {1,0,0,1}
            };
            color2.add(time, 2, p);
            m_behaviour.addColor(1.0f, &color2);
        }

        {
            float p[] { 10,50,20,5};
            size1.add(time, 4, p);
            m_behaviour.addSize(1.0f, &size1);
        }
        {
            float p[] { 50,5,10,50};
            size2.add(time, 4, p);
            m_behaviour.addSize(1.0f, &size2);
        }

        fireParticle(&m_behaviour);
        return JAWE::Updater::init();
    }

    void Updater::fireParticle(const Behaviour *pBehaviour)
    {
        particle_ptr p = m_particleBank.pop();
        p->fire(pBehaviour);
        m_itemsToAdd.push_back(p);
        pBehaviour->fire(m_generator, p.get());
    }

    void Updater::advance(float dt)
    {
        m_particleCollector.begin();
        for(auto it = m_items.begin(); it != m_items.end();)
        {
            if(!(*it)->update(m_particleCollector, dt))
            {
                m_particleBank.push(*it);
                it = m_items.erase(it);
                //temp
                fireParticle(&m_behaviour);
            }
            else
                ++it;
        }

        {
            std::lock_guard<std::mutex> _(m_particleMutex);
            m_particleCollector.end(m_particles);
        }

        for(auto& it : m_itemsToAdd)
            m_items.push_back(it);
        m_itemsToAdd.clear();
    }

    void Updater::updateInstances(particle_mesh& mesh)
    {
        std::lock_guard<std::mutex> _(m_particleMutex);
        mesh.updateInstances(m_particles.size(), m_particles.size() == 0 ? nullptr : &m_particles[0]);
    }
}
