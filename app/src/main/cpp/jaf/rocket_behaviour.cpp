#include "rocket_behaviour.h"
#include "update_data.h"

namespace JAF {

	void RocketBehaviour::start(BehaviourInfluenced* pItem, const Math::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		TransformData* pData = m_data.pop();
		pData->factors = {1,1,1};

		Math::Vector3 p = m_offset;
		switch(m_offsetType)
		{
			default:
				break;
			case LINE:
				p.normalize();
				p = m_offset - (p * m_tag * static_cast<float>(m_nrReleased));
				break;
			case CIRCLE:
				p = Math::Matrix::transform(Math::Matrix::setRotate(0, static_cast<float>(m_nrReleased) * m_tag, 0), p, 0.0f);
				pData->factors = p;
				pData->factors.normalize();
				pData->factors.y(1);
				break;
		}

		pData->offset = offset.transform(p);

		pItem->setData(pData);

		pParticle->fire(this);
		++m_nrReleased;
	}

	bool RocketBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(time >= m_timeLimit)
		{
			Math::Matrix offset = pItem->calculateTransform();
			for(auto& it : m_bursts)
			{
				Particle* p = pUpdateData->pUpdater->fireParticle();
				it->start(p, offset);
			}

			return false;
		}

		float delta = time / m_timeLimit;

		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		Math::Vector3 p = pData->offset + (PathBehaviour::update<Math::Vector3>({0,0,0}, m_positions, delta) * pData->factors);

		pItem->setPosition(p);
		pItem->setRadius(0);

		for(auto& it : m_trails)
		{
			if((it.time -= pUpdateData->dt) <= 0)
			{
				it.time += it.interval;
				Math::Matrix t = pItem->calculateTransform();
				Particle* p = pUpdateData->pUpdater->fireParticle();
				it.pBehaviour->start(p, t);
			}
		}

		return true;
	}
}