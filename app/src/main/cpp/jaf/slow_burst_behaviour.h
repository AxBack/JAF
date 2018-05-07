#pragma once

#include "burst_behaviour.h"

namespace JAF {

	class SlowBurstBehaviour : public Behaviour
	{
	private:

		struct Release
		{
			UINT nrPerRelease;
			float interval;
			Behaviour* pBehaviour;
		};

		struct IntervalData
		{
			UINT releaseIndex;
			float counter;
		};

		struct Data : public BehaviourInfluenced::Data
		{
			Math::Matrix offset;
			std::vector<IntervalData> intervalData;
		};

		std::vector<Release> m_releases;

		typedef JAWE::Bank<Data*> data_bank;
		data_bank m_data {[this](){ return new Data(); }, [](Data* p) { delete p; }};

	public:

		virtual void clear() override
		{
			for(auto& it : m_releases)
				it.pBehaviour->decrementUsers();
			m_releases.clear();
		}

		void add(UINT nr, float interval, Behaviour* pBehaviour)
		{
			m_releases.push_back({nr, interval, pBehaviour->incrementUsers()});
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			Data* pData = reinterpret_cast<Data*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
}