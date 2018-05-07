#pragma once

#include "../jawe/bank.h"
#include "burst_behaviour.h"

namespace JAF {

	class SlowBurstBehaviour : public BurstBehaviour
	{
	private:

		struct Release
		{
			UINT nrPerRelease;
			float interval;
			Behaviour* pBehaviour;
		};

		struct ReleaseData : public BurstBehaviour::Data
		{
			UINT releaseIndex;
			float counter;
		};

		virtual Data* createData() { return new ReleaseData(); }

		void update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, ReleaseData* pData, float time)
		{
			// update and release necessary particles.
		}

	public:

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
		{
			if(!BurstBehaviour::update(pUpdateData, pItem, time))
				return false;

			ReleaseData* pData = reinterpret_cast<ReleaseData*>(pItem->getData());
			if(pData == nullptr)
				return false;

			update(pUpdateData, pItem, pData, time);
			return true;
		}
	};
}