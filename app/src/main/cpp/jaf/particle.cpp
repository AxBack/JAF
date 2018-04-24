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
		m_lastPosition = m_position;
		m_position = position * m_factors;
        Math::Vector3 p = m_position;
        if (m_pOffset)
            p = m_pOffset->transform(p);

        m_instance.x = p.x();
        m_instance.y = p.y();
        m_instance.z = p.z();
    }

    auto Particle::calculateTransform() const->matrix_ptr
    {
        Math::Vector3 up = {0,1,0};
        if (m_pOffset)
            up = m_pOffset->transform(up, 0.0f);

		matrix_ptr p(new Math::Matrix);
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

        if(m_pOffset)
            t = Math::Matrix::multiply(*m_pOffset.get(), t);

        return p;
    }

    Math::Quaternion Particle::calculateRotation(const Math::Vector3& up) const
    {
        Math::Vector3 normal = m_position - m_lastPosition;
        if (normal.lengthSq() == 0)
            return Math::Quaternion::identity();

        normal.normalize();
        return Math::Quaternion::rotationBetweenNormals(up, normal);
    }
}
