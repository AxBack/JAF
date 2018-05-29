#pragma once

#include "burst_behaviour.h"

namespace JAF {

	class SlowBurstBehaviour : public Behaviour
	{
	private:

		typedef std::vector<float> float_vec;
		typedef JAWE::Path<JAWE::MATH::Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		struct Release
		{
			UINT nrPerInterval;
			float interval;
			vec3_path* pRotation;
			Behaviour* pBehaviour;
			UINT nrPerCircle;
		};

		struct Data : public BehaviourInfluenced::Data
		{
			JAWE::MATH::Matrix offset;
			float_vec counters;
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

		void add(UINT nrPerIRelease, float interval, vec3_path* pRotation, Behaviour* pBehaviour, UINT nrPerCircle)
		{
			m_releases.push_back({nrPerIRelease, interval, pRotation, pBehaviour->incrementUsers(), nrPerCircle});
		}

		virtual void start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			Data* pData = reinterpret_cast<Data*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
}