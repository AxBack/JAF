#include "trail_behaviour.h"
#include "particle.h"

namespace JAF {

	void TrailBehaviour::start(BehaviourInfluenced* pItem, const Math::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		TransformData* pData = m_data.pop();

		Math::Vector3 dir {JAWE::Random::randf(-m_dispersion, m_dispersion), 1, JAWE::Random::randf(-m_dispersion, m_dispersion)};
		dir.normalize();
		dir *= 50.0f;
		pData->force = offset.transform(dir, 0.0f);
		pData->position = offset.transform({0,0,0});
		pData->time = 0.0f;
		pItem->setData(pData);

		pParticle->fire(this);
	}

	bool TrailBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(time >= m_timeLimit)
			return false;

		float delta = time / m_timeLimit;

		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		float dt  = time - pData->time;
		pData->time = time;

		pData->force += (pData->force * -dt) + m_gravity * dt;
		pData->position += pData->force * dt;

		pItem->setPosition(pData->position);
		pItem->setRadius(m_size.update(0.0f, delta));
		pItem->setColor(m_color.update({0,0,0,0}, delta));

		return true;
	}
}