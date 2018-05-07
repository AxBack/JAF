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
		p->intervalData.clear();
		for(UINT i=0; i<m_releases.size(); ++i)
			p->intervalData.push_back({i, m_releases[i].interval});

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

		for(auto& it : pData->intervalData)
		{
			it.counter -= pUpdateData->dt;
			if(it.counter <= 0)
			{
				Math::Matrix offset = pItem->calculateTransform();

				const Release* pRelease = &m_releases[it.releaseIndex];
				it.counter += pRelease->interval;

				for(UINT i = 0; i < pRelease->nrPerRelease; ++i)
				{
					Particle* p = pUpdateData->pUpdater->fireParticle();
					pRelease->pBehaviour->start(p, offset);
				}
			}
		}

		return true;
	}
}