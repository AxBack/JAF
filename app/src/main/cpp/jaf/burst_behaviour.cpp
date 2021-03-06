#include "burst_behaviour.h"
#include "particle.h"
#include "update_data.h"

namespace JAF {

	void BurstBehaviour::start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		Data* pData = getData();
		if(m_gravity.lengthSq() <= 0)
		{
			pData->offset = calculateOffset(offset);
			pData->positionWeights = m_position.deviate(m_positionDeviation);
		}
		else
		{
			float_vec dev = m_position.deviate(m_positionDeviation);
			JAWE::MATH::Matrix t = calculateOffset(offset);
			pData->position = offset.transform({0,0,0}, 1);
			pData->force =  t.transform(m_position.update({0,0,0}, dev, JAWE::Random::randf(0.5f, 1.0f)), 0);
		}

		if(m_allowedDeviation != 0.0f)
			pData->deviation = JAWE::Random::randf(-m_allowedDeviation, m_allowedDeviation);
		else
			pData->deviation = 0.0f;

		pData->sizeWeights = m_size.deviate(m_sizeDeviation);
		pData->colorWeights = m_color.deviate(m_colorDeviation);

		pParticle->fire(this);
		pParticle->setData(pData);
		pParticle->setPosition(offset.transform({0,0,0}, 1));
	}

	bool BurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		Data* pData = reinterpret_cast<Data*>(pItem->getData());
		float limit = m_timeLimit + pData->deviation;
		if(time >= limit)
			return false;

		float delta = time / limit;

		if(pData->positionWeights.size() > 0)
		{
			JAWE::MATH::Vector3 p = pData->offset.transform(m_position.update({0, 0, 0}, pData->positionWeights, delta), 1);
			pItem->setPosition(p);
		}
		else
		{
			float factor = -0.1f;
			pData->force += pData->force * (factor * pUpdateData->dt) + (m_gravity * pUpdateData->dt);
			pData->position += pData->force * pUpdateData->dt;
			pItem->setPosition(pData->position);
		}

		pItem->setRadius(m_size.update(0.0f, pData->sizeWeights, delta));
		pItem->setColor(m_color.update({0,0,0,0}, pData->colorWeights, delta));

		return true;
	}

}