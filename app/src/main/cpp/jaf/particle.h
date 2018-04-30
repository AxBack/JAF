#pragma once

#include "behaviour.h"
#include "../jawe/instance_collector.h"
#include "../jawe/quaternion.h"
#include "vertex.h"

namespace JAF {

	class Particle;
	struct UpdateData;

	class ParticleListener
	{
	public:
		virtual void onDead(const Particle* p) = 0;
	};

    class Particle : public BehaviourInfluenced
    {
    private:

		ParticleListener* m_pListener { nullptr };

        int m_type { 0 };

		Math::Vector3 m_position { 0,0,0 };
		Math::Vector3 m_lastPosition { 0,0,0 };

        ParticleInstance m_instance;

        float m_time { 0 };
		Behaviour* m_pBehaviour { nullptr };

    public:

		void clear()
		{
            m_type = 0;
			m_pListener = nullptr;
			m_pBehaviour = nullptr;
			m_position = m_lastPosition = {0,0,0};
		}

		void setListener(ParticleListener* pListener) { m_pListener = pListener; }

        void fire(Behaviour* pBehaviour);

        bool update(UpdateData* pData);

        virtual Math::Matrix calculateTransform() const override;
		Math::Quaternion calculateRotation(const Math::Vector3& up = {0,1,0}) const;

        void setType(int type) { m_type = type; }
        int getType() const { return m_type; }

        virtual void setPosition(const Math::Vector3& position) override;

        virtual void setRadius(const float radius) override
        {
            m_instance.radius = radius;
        }

        virtual void setColor(const Math::Color& color) override
        {
            m_instance.a = color.a();
            m_instance.r = color.r();
            m_instance.g = color.g();
            m_instance.b = color.b();
        }
    };
}