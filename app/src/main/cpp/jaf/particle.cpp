#include "particle.h"

#include "update_data.h"

namespace JAF {

    void Particle::fire(ParticleListener* pListener, Behaviour* pBehaviour, const Math::Matrix& offset)
    {
        m_time = 0;
		m_pListener = pListener;
        m_pBehaviour = pBehaviour;
		m_pBehaviour->incrementUsers();
		m_pBehaviour->start(this, offset);
    }

    bool Particle::update(UpdateData* pData)
    {
        m_time += pData->dt;
        if(!m_pBehaviour->update(pData, this, m_time))
        {
			m_pBehaviour->end(this);
			m_pBehaviour->decrementUsers();
            if(m_pListener)
				m_pListener->onDead(this);
            return false;
        }

        if (m_instance.radius > 0 && m_instance.a > 0)
            pData->pInstanceCollector->add(m_instance);

		if(m_pListener != nullptr && m_interval > 0 && (m_counter -= pData->dt) <= 0)
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

    Math::Matrix Particle::calculateTransform() const
    {
        Math::Vector3 up = {0,1,0};

		Math::Matrix t;
		Math::Matrix::identity(t);
		Math::Matrix::translate(t, m_position);

        Math::Quaternion rot = calculateRotation(up);
		if(!rot.isIdentity())
		{
			Math::Matrix r;
			Math::Matrix::setRotate(r, rot);
			t = t * r;
		}

        return std::move(t);
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
