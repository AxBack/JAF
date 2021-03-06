#include "particle.h"

#include "update_data.h"

namespace JAF {

    void Particle::fire(Behaviour* pBehaviour)
    {
        m_time = 0;
        m_pBehaviour = pBehaviour;
		m_pBehaviour->incrementUsers();
		m_lastPosition = m_position = {0,0,0};
    }

    bool Particle::update(UpdateData* pData)
    {
        m_time += pData->dt;
        if(!m_pBehaviour->update(pData, this, m_time))
        {
			m_pBehaviour->end(this);
			m_pBehaviour->decrementUsers();
            if(m_pListener)
			{
				m_pListener->onDead(this);
				m_pListener = nullptr;
			}
            return false;
        }

        if (m_instance.radius > 0 && m_instance.a > 0)
            pData->pInstanceCollector->add(m_instance);

        return true;
    }

    void Particle::setPosition(const JAWE::MATH::Vector3& position)
    {
		m_lastPosition = m_position;
		m_position = position;

        m_instance.x = m_position.x();
        m_instance.y = m_position.y();
        m_instance.z = m_position.z();
    }

	JAWE::MATH::Matrix Particle::calculateTransform() const
    {
		JAWE::MATH::Vector3 up = {0,1,0};

		JAWE::MATH::Matrix t;
		JAWE::MATH::Matrix::setIdentity(t);
		JAWE::MATH::Matrix::translate(t, m_position);

		JAWE::MATH::Quaternion rot = calculateRotation(up);
		if(!rot.isIdentity())
		{
			JAWE::MATH::Matrix r;
			JAWE::MATH::Matrix::setRotate(r, rot);
			t = t * r;
		}

        return std::move(t);
    }

	JAWE::MATH::Quaternion Particle::calculateRotation(const JAWE::MATH::Vector3& up) const
    {
		JAWE::MATH::Vector3 normal = m_position - m_lastPosition;
        if (normal.lengthSq() == 0)
            return JAWE::MATH::Quaternion::identity();

        normal.normalize();
        return JAWE::MATH::Quaternion::rotationBetweenNormals(normal, up);
    }
}
