#pragma once

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

		struct IntervalData
		{
			UINT releaseIndex;
			float counter;
		};

		struct ReleaseData : public BurstBehaviour::Data
		{
			std::vector<IntervalData> intervalData;
		};

		std::vector<Release> m_releases;

		virtual Data* createData() override { return new ReleaseData(); }

		void update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, ReleaseData* pData, float time);

	public:

		virtual void clear() override
		{
			BurstBehaviour::clear();

			for(auto& it : m_releases)
				it.pBehaviour->decrementUsers();
			m_releases.clear();
		}

		void add(UINT nr, float interval, Behaviour* pBehaviour)
		{
			m_releases.push_back({nr, interval, pBehaviour->incrementUsers()});
		}

		virtual void start(Particle* pParticle, Data* pData, const Math::Matrix& offset) override
		{
			ReleaseData* p = reinterpret_cast<ReleaseData*>(pData);
			for(UINT i=0; 0<m_releases.size(); ++i)
				p->intervalData.push_back({i, m_releases[i].interval});

			BurstBehaviour::start(pParticle, pData, offset);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
}