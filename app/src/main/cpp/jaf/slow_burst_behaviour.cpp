#include "slow_burst_behaviour.h"

#include "update_data.h"

namespace JAF {

	void SlowBurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, ReleaseData* pData, float time)
	{
		for(auto& it : pData->intervalData)
		{
			it.counter -= pUpdateData->dt;
			if(it.counter <= 0)
			{
				Math::Matrix offset = pItem->calculateTransform();

				Release* pRelease = &m_releases[it.releaseIndex];
				it.counter += pRelease->interval;

				for(UINT i = 0; i < pRelease->nrPerRelease; ++i)
				{
					Particle* p = pUpdateData->pUpdater->fireParticle();
					pRelease->pBehaviour->start(p, offset);
				}
			}
		}
	}

	bool SlowBurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(!BurstBehaviour::update(pUpdateData, pItem, time))
			return false;

		ReleaseData* pData = reinterpret_cast<ReleaseData*>(pItem->getData());
		if(pData == nullptr)
			return false;

		update(pUpdateData, pItem, pData, time);
		return true;
	}
}