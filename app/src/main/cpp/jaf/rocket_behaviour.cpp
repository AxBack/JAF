#include "rocket_behaviour.h"
#include "update_data.h"

namespace JAF {

	void RocketBehaviour::start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		TransformData* pData = m_data.pop();
		pData->factors = {1,1,1};
		if(m_allowedDeviation != 0.0f)
			pData->deviation = JAWE::Random::randf(-m_allowedDeviation, m_allowedDeviation);
		else
			pData->deviation = 0.0f;

		pData->weights = m_position.deviate(m_positionDeviation);

		JAWE::MATH::Vector3 p = m_offset;
		switch(m_offsetType)
		{
			default:
				break;
			case LINE:
				p.normalize();
				p = m_offset - (p * m_tag * static_cast<float>(m_nrReleased));
				break;
			case CIRCLE:
				p = JAWE::MATH::Matrix::transform(JAWE::MATH::Matrix::setRotate(0, static_cast<float>(m_nrReleased) * m_tag, 0), p, 0.0f);
				pData->factors = p;
				pData->factors.normalize();
				pData->factors.y(1);
				break;
		}

		pData->offset = offset.transform(p);
		for(auto& it : m_trails)
			pData->counters.push_back(it.interval);

		pItem->setData(pData);

		pParticle->fire(this);
		++m_nrReleased;
	}

	bool RocketBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		float limit = m_timeLimit + pData->deviation;
		if(time >= limit)
		{
			JAWE::MATH::Matrix offset = pItem->calculateTransform();
			for(auto& it : m_bursts)
			{
				for(UINT i=0; i<it.nr; ++i)
				{
					Particle* p = pUpdateData->pUpdater->fireParticle();
					it.pBehaviour->start(p, offset);
				}
			}

			return false;
		}

		float delta = time / limit;

		JAWE::MATH::Vector3 p = pData->offset + (m_position.update({0,0,0}, pData->weights, delta) * pData->factors);

		pItem->setPosition(p);
		pItem->setRadius(0);

		for(UINT i=0; i<pData->counters.size(); ++i)
		{
			float& counter = pData->counters[i];
			if((counter -= pUpdateData->dt) <= 0)
			{
				counter += m_trails[i].interval;
				JAWE::MATH::Matrix t = pItem->calculateTransform();
				Particle* p = pUpdateData->pUpdater->fireParticle();
				m_trails[i].pBehaviour->start(p, t);
			}
		}

		return true;
	}
}