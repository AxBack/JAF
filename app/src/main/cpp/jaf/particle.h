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

        typedef std::shared_ptr<Math::Matrix> matrix_ptr;

		ParticleListener* m_pListener { nullptr };

        int m_type { 0 };

        matrix_ptr m_pOffset;
		Math::Vector3 m_factors{ 1,1,1 };
		Math::Vector3 m_lastPosition { 0,0,0 };

        ParticleInstance m_instance;

        float m_time { 0 };
        const Behaviour* m_pBehaviour { nullptr };

		Math::Vector3 getPosition() const { return {m_instance.x, m_instance.y, m_instance.z};}

    public:

		void clear()
		{
            m_type = 0;
		}

        void fire(ParticleListener* pListener, std::mt19937& generator, const Behaviour* pBehaviour);

        bool update(InstanceCollector<ParticleInstance>& collector, float dt);

        Math::Matrix calculateTransform() const;
		Math::Quaternion calculateRotation(const Math::Vector3& up = {0,1,0}) const;

		void setOffset(matrix_ptr pOffset) { m_pOffset = pOffset; }
		void setFactors(const Math::Vector3& factors) { m_factors = factors; }

        void setType(int type) { m_type = type; }
        int getType() const { return m_type; }

        virtual void setPosition(const Math::Vector3& position) override;

        virtual void setSize(const float size) override
        {
            m_instance.size = size;
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