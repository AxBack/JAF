#pragma once

#include "instance_collector.h"
#include "vertex.h"
#include "behaviour.h"

namespace JAF {

    class Particle : public BehaviourInfluenced
    {
    private:

        ParticleInstance m_instance;

        float m_time;
        const Behaviour* m_pBehaviour;

    public:

        Particle()
                : m_time(0.0f)
                , m_pBehaviour(nullptr)
        {}

        void fire(const Behaviour* pBehaviour);

        bool update(InstanceCollector<ParticleInstance>& collector, float dt);

        virtual void setPosition(const Math::Vector3& position)
        {
            m_instance.x = position.x();
            m_instance.y = position.y();
            m_instance.z = position.z();
        }

        virtual void setSize(const float size)
        {
            m_instance.size = size;
        }

        virtual void setColor(const Math::Color& color)
        {
            m_instance.a = color.a();
            m_instance.r = color.r();
            m_instance.g = color.g();
            m_instance.b = color.b();
        }
    };
}