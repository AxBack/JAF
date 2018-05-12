#include "slow_burst_behaviour.h"

#include "update_data.h"

namespace JAF {

	void SlowBurstBehaviour::start(BehaviourInfluenced* pItem, const Math::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		Data* p = m_data.pop();
		p->offset = offset;
		p->counters.clear();
		for(auto& it : m_releases)
			p->counters.push_back(it.interval);
		p->offset = offset;

		pParticle->fire(this);
		pParticle->setData(p);
		pParticle->setPosition(offset.transform({0,0,0}, 1));
	}

	bool SlowBurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(time >= m_timeLimit)
			return false;

		Data* pData = reinterpret_cast<Data*>(pItem->getData());
		if(pData == nullptr)
			return false;

		for(UINT i = 0; i<pData->counters.size(); ++i)
		{
			Release* pRelease = &m_releases[i];
			pData->counters[i] -= pUpdateData->dt;
			if(pData->counters[i] <= 0)
			{
				Math::Vector3 rot = pRelease->pRotation->traverse(time);
				Math::Matrix direction = Math::Matrix::setRotate(rot.x(), rot.y(), rot.z());
				Math::Matrix transform = pItem->calculateTransform() * direction;
				for(UINT o=0; o<pRelease->nrOffsets; ++o)
				{
					Math::Matrix offset = transform * pRelease->pOffsets[o];
					pData->counters[i] += pRelease->interval;
					for(UINT particle = 0; particle < pRelease->nrPerInterval; ++particle)
					{
						Particle* p = pUpdateData->pUpdater->fireParticle();
						pRelease->pBehaviour->start(p, offset);
					}
				}
			}
		}

		return true;
	}
}