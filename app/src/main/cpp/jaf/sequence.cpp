#include "sequence.h"

#include "updater.h"
#include "../jawe/random.h"

namespace JAF {

	void Sequence::fire(const Behaviour* pBehaviour, matrix_ptr pOffset, const Math::Vector3& factors)
	{
		Particle* p = m_pUpdater->fireParticle();
		p->setOffset(pOffset);
		p->setFactors(factors);
		p->fire(nullptr, pBehaviour);
	}

	void Sequence::fireRelevant(const Behaviour* pBehaviour, matrix_ptr pOffset, int type, const Math::Vector3& factors)
	{
		++m_nrRelevantParticles;
		Particle* p = m_pUpdater->fireParticle();
		p->setType(type);
		p->setOffset(pOffset);
		p->setFactors(factors);
		p->setInterval(0.01f);
		p->fire(this, pBehaviour);
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
				float x = JAWE::Random::rand(-180, 180);
				float z = JAWE::Random::rand(-180, 180);

				matrix_ptr offset(new Math::Matrix);
				Math::Matrix& t = *offset.get();
				Math::Matrix::setRotate(*offset.get(), x, 0, z);
				t = *p.get() * t;

				fire(m_pFlare, offset, {1,-1,1});
			}
        }
	}

	void Sequence::onInterval(const Particle* pParticle)
	{
		matrix_ptr p = pParticle->calculateTransform();
		Math::Vector3 factors {JAWE::Random::rand(-1, 1), 1, JAWE::Random::rand(-1, 1)};
		fire(m_pTrail, p, factors);
	}

	void Sequence::update(float dt)
	{

	}

}