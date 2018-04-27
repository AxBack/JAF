#include "particle.h"

namespace JAF {

    void Particle::fire(ParticleListener* pListener, Behaviour* pBehaviour, std::shared_ptr<Math::Matrix> pOffset)
    {
        m_time = 0;
		m_pListener = pListener;
        m_pBehaviour = pBehaviour;
		m_pBehaviour->start(this, *pOffset.get());
    }

    bool Particle::update(InstanceCollector<ParticleInstance>& collector, float dt)
    {
        m_time += dt;
        if(!m_pBehaviour->update(this, m_time))
        {
			m_pBehaviour->end(this);
            if(m_pListener)
				m_pListener->onDead(this);
            return false;
        }

        if (m_instance.radius > 0 && m_instance.a > 0)
            collector.add(m_instance);

		if(m_pListener != nullptr && m_interval > 0 && (m_counter -= dt) <= 0)
		{
			m_counter += m_interval;
			m_pListener->onInterval(this);
		}

        return true;
    }

    void Particle::setPosition(const Math::Vector3& position)
    {
		m_lastPosition = m_position;
		m_position = position;

        m_instance.x = m_position.x();
        m_instance.y = m_position.y();
        m_instance.z = m_position.z();
    }

    auto Particle::calculateTransform() const->std::shared_ptr<Math::Matrix>
    {
        Math::Vector3 up = {0,1,0};

		std::shared_ptr<Math::Matrix> p(new Math::Matrix);
		Math::Matrix& t = *p.get();
		Math::Matrix::identity(t);
		Math::Matrix::translate(t, m_position);

        Math::Quaternion rot = calculateRotation(up);
		if(!rot.isIdentity())
		{
			Math::Matrix r;
			Math::Matrix::setRotate(r, rot);
			t = t * r;
		}

        return p;
    }

    Math::Quaternion Particle::calculateRotation(const Math::Vector3& up) const
    {
        Math::Vector3 normal = m_position - m_lastPosition;
        if (normal.lengthSq() == 0)
            return Math::Quaternion::identity();

        normal.normalize();
        return Math::Quaternion::rotationBetweenNormals(normal, up);
    }
}
