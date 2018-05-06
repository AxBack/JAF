#pragma once

#include "behaviour.h"

namespace JAF {

	class SlowBurstBehaviour : public Behaviour
	{
	private:

	public:

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override
		{

		}

		virtual void end(BehaviourInfluenced* pItem) override
		{
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override
		{

			return false;
		}
	};
}