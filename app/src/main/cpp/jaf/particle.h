#pragma once

#include "vertex.h"
#include "behaviour.h"
#include "../jawe/instance_collector.h"
#include "../jawe/quaternion.h"

namespace JAF {

	class Particle;

	class ParticleListener
	{
	public:
		virtual void onDead(const Particle* p) = 0;
	};

    class Particle : public BehaviourInfluenced
    {
    private:

		ParticleListener* m_pListener;

		Math::Vector3 m_offset;
		Math::Vector3 m_factors;
		Math::Vector3 m_lastPosition;

        ParticleInstance m_instance;

        float m_time;
        const Behaviour* m_pBehaviour;

		Math::Vector3 getPosition() const { return {m_instance.x, m_instance.y, m_instance.z};}

    public:

        Particle()
                : m_time(0.0f)
                , m_pBehaviour(nullptr)
				, m_offset(0,0,0)
				, m_lastPosition(0,0,0)
				, m_factors(1,1,1)
				, m_pListener(nullptr)
        {}

		void clear()
		{
		}

        void fire(ParticleListener* pListener, std::mt19937& generator, const Behaviour* pBehaviour);

        bool update(InstanceCollector<ParticleInstance>& collector, float dt);

		Math::Quaternion calculateRotation() const;

		void setOffset(const Math::Vector3& offset) { m_offset = offset; }
		void setFactors(const Math::Vector3& factors) { m_factors = factors; }

        virtual void setPosition(const Math::Vector3& position)
        {
			m_lastPosition = getPosition();
			Math::Vector3 p = position * m_factors;
            m_instance.x = m_offset.x() + p.x();
            m_instance.y = m_offset.y() + p.y();
            m_instance.z = m_offset.z() + p.z();
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