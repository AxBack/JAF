#include "updater.h"

namespace JAF {

    bool Updater::init()
    {
        float time = 3.0f;
        m_rocketBehaviour.init(time);
		m_explosionBeaviour.init(time);
        {
            Math::Vector3 p[] {
                    {0,0,0},
                    {300,150,300},
                    {0,300,0},
                    {-300,450,-300},
                    {0,600,0},
            };
            position1.add(time, 5, p);
			m_rocketBehaviour.addPosition(1.0f, &position1);
        }
        {
            Math::Vector3 p[] {
                    {0,0,0},
                    {-300,150,-300},
                    {0,300,0},
                    {300,450,300},
                    {0,600,0}
            };
            position2.add(time, 5, p);
			m_rocketBehaviour.addPosition(1.0f, &position2);
        }

		{
			Math::Vector3 p[] {
					{0,0,0},
					{100,100,100}
			};
			position3.add(time, 5, p);
			m_explosionBeaviour.addPosition(1.0f, &position3);
		}
		{
			Math::Vector3 p[] {
					{0,0,0},
					{-100,-100,-100}
			};
			position4.add(time, 5, p);
			m_explosionBeaviour.addPosition(1.0f, &position4);
		}

        {
            Math::Color p[] {
                    {1,0,1,1},
                    {1,1,0,1}
            };
            color1.add(time, 2, p);
			m_rocketBehaviour.addColor(1.0f, &color1);
			m_explosionBeaviour.addColor(1.0f, &color1);
        }
        {
            Math::Color p[] {
                    {0,0,1,1},
                    {1,0,0,1}
            };
            color2.add(time, 2, p);
			m_rocketBehaviour.addColor(1.0f, &color2);
			m_explosionBeaviour.addColor(1.0f, &color2);
        }

        {
            float p[] { 2,6,5,1};
            size1.add(time, 4, p);
			m_rocketBehaviour.addSize(1.0f, &size1);
			m_explosionBeaviour.addSize(1.0f, &size1);
        }
        {
            float p[] { 3,15,25,2};
            size2.add(time, 4, p);
			m_rocketBehaviour.addSize(1.0f, &size2);
			m_explosionBeaviour.addSize(1.0f, &size2);
        }

		fireParticle(&m_rocketBehaviour, {0,-300,0});
        return JAWE::Updater::init();
    }

    void Updater::fireParticle(const Behaviour *pBehaviour, const Math::Vector3& offset)
    {

        particle_ptr p = m_particleBank.pop();
		p->clear();
        p->fire(pBehaviour);
		if(pBehaviour == &m_rocketBehaviour)
			p->addOnEndRelease(10, &m_explosionBeaviour);
        m_itemsToAdd.push_back(p);
        p->setOffset(offset);
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
            }
            else
                ++it;
        }

        {
            std::lock_guard<std::mutex> _(m_particleMutex);
            m_particleCollector.end(m_particles);
        }

        //temp
		/*
        m_counter -= dt;
        if(m_counter <= 0)
        {
            m_counter += 0.05f;
            for(int i=0; i<3; ++i)
                fireParticle(&m_behaviour, {0,-300, 0});
        }
        */

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
