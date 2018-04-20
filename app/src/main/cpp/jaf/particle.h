#pragma once

#include "vertex.h"
#include "behaviour.h"
#include "../jawe/instance_collector.h"

namespace JAF {

	class OnReleaseListener
	{
	public:
		virtual void onRelease(int nr, const Math::Vector3& offset, const Behaviour* pBehaviour) = 0;
	};

    class Particle : public BehaviourInfluenced
    {
    private:

		struct Release
		{
			UINT nr;
			const Behaviour* pBehaviour;
		};

		OnReleaseListener* m_pOnReleaseListener;

		std::vector<Release> m_onEndReleases;

		Math::Vector3 m_offset;
        ParticleInstance m_instance;

        float m_time;
        const Behaviour* m_pBehaviour;

    public:

        Particle(OnReleaseListener* pOnReleaseListener)
                : m_time(0.0f)
                , m_pBehaviour(nullptr)
				, m_offset(0,0,0)
				, m_pOnReleaseListener(pOnReleaseListener)
        {}

		void clear()
		{
			m_onEndReleases.clear();
		}

		void addOnEndRelease(UINT nr, const Behaviour* pBehaviour)
		{
			m_onEndReleases.push_back({nr, pBehaviour});
		}

        void fire(const Behaviour* pBehaviour);

        bool update(InstanceCollector<ParticleInstance>& collector, float dt);

		virtual void setOffset(const Math::Vector3& offset) { m_offset = offset; }

        virtual void setPosition(const Math::Vector3& position)
        {
            m_instance.x = m_offset.x() + position.x();
            m_instance.y = m_offset.y() + position.y();
            m_instance.z = m_offset.z() + position.z();
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