#include "trail_behaviour.h"
#include "particle.h"
#include "update_data.h"

namespace JAF {

	void TrailBehaviour::start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		TransformData* pData = m_data.pop();

		JAWE::MATH::Vector3 dir {JAWE::Random::randf(-m_dispersion, m_dispersion), 1, JAWE::Random::randf(-m_dispersion, m_dispersion)};
		dir.normalize();
		dir *= 50.0f;
		pData->force = offset.transform(dir, 0.0f);
		pData->position = offset.transform({0,0,0});
		pData->sizeWeights = m_size.deviate(m_sizeDeviation);
		pData->colorWeights = m_color.deviate(m_colorDeviation);

		if(m_allowedDeviation != 0.0f)
			pData->deviation = JAWE::Random::randf(-m_allowedDeviation, m_allowedDeviation);
		else
			pData->deviation = 0.0f;

		pItem->setData(pData);

		pParticle->fire(this);
	}

	bool TrailBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		float limit = m_timeLimit + pData->deviation;
		if(time >= limit)
			return false;

		float delta = time / limit;

		float dt = pUpdateData->dt;
		pData->force += (pData->force * -dt) + m_gravity * dt;
		pData->position += pData->force * dt;

		pItem->setPosition(pData->position);
		pItem->setRadius(m_size.update(0.0f, pData->sizeWeights, delta));
		pItem->setColor(m_color.update({0,0,0,0}, pData->colorWeights, delta));

		return true;
	}
}