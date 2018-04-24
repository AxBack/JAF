#include "sequence.h"

#include "updater.h"

namespace JAF {

	void Sequence::fire(const Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factor) const
	{
		m_pUpdater->fireParticle(nullptr, pBehaviour, pOffset, -1, factor);
	}

	void Sequence::fireRelevant(const Behaviour* pBehaviour, matrix_ptr pOffset, int type, const Math::Vector3& factor)
	{
		++m_nrRelevantParticles;
		m_pUpdater->fireParticle(this, pBehaviour, pOffset, type, factor);
	}

	void Sequence::start()
	{
		//temp
        matrix_ptr p(new Math::Matrix);
        p->setIdentity();
        p->translate(0,-300,0);
		fireRelevant(m_pRocket, p, 84);
	}

	void Sequence::onDead(const Particle* pParticle)
	{
		--m_nrRelevantParticles;
        if (pParticle->getType() == 84)
        {
			std::uniform_real_distribution<float> dist(-180, 180);
			matrix_ptr p = pParticle->calculateTransform();
			for(int i=0; i<100; ++i)
			{
				float x = dist(m_generator);
				float z = dist(m_generator);

				matrix_ptr offset(new Math::Matrix);
				Math::Matrix& t = *offset.get();
				Math::Matrix::setRotate(*offset.get(), x, 0, z);
				t = *p.get() * t;

				fire(m_pFlare, offset, {1,-1,1});
			}
        }
	}

	void Sequence::update(float dt)
	{

	}

}