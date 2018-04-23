#include "particle.h"

namespace JAF {

    void Particle::fire(ParticleListener* pListener, std::mt19937& generator, const Behaviour* pBehaviour)
    {
        m_time = 0;
		m_pListener = pListener;
        m_pBehaviour = pBehaviour;
		pBehaviour->fire(generator, this);
    }

    bool Particle::update(InstanceCollector<ParticleInstance>& collector, float dt)
    {
        m_time += dt;
        if(!m_pBehaviour->update(this, m_time))
        {
            if(m_pListener)
				m_pListener->onDead(this);
            return false;
        }

        if (m_instance.size > 0 && m_instance.a > 0)
            collector.add(m_instance);

        return true;
    }

    void Particle::setPosition(const Math::Vector3& position)
    {
        Math::Vector3 p = position * m_factors;
        if (m_pOffset)
            p = m_pOffset->transform(p);

        m_lastPosition = getPosition();
        m_instance.x = p.x();
        m_instance.y = p.y();
        m_instance.z = p.z();
    }

    Math::Matrix Particle::calculateTransform() const
    {
        Math::Vector3 up = {0,1,0};
        if (m_pOffset)
            up = m_pOffset->transform(up);

        Math::Quaternion rot = calculateRotation(up);

        Math::Matrix t;
        Math::Matrix::setRotate(t, rot);
        Math::Matrix::translate(t, m_instance.x, m_instance.y, m_instance.z);

        if(m_pOffset)
            t = Math::Matrix::multiply(t, *m_pOffset.get());

        return std::move(t);
    }

    Math::Quaternion Particle::calculateRotation(const Math::Vector3& up) const
    {
        Math::Vector3 normal = getPosition() - m_lastPosition;
        if (normal.lengthSq() == 0)
            return Math::Quaternion::identity();

        normal.normalize();
        return Math::Quaternion::rotationBetweenNormals(up, normal);
    }
}
