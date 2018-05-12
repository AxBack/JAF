#pragma once

#include "burst_behaviour.h"

namespace JAF {

	class SlowBurstBehaviour : public Behaviour
	{
	private:

		typedef std::vector<float> float_vec;
		typedef JAWE::Path<Math::Vector3> vec3_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;

		struct Release
		{
			UINT nrPerInterval;
			float interval;
			vec3_path* pRotation;
			Behaviour* pBehaviour;
			UINT nrOffsets;
			const Math::Matrix* pOffsets;
		};

		struct Data : public BehaviourInfluenced::Data
		{
			Math::Matrix offset;
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

		void add(UINT nrPerIRelease, float interval, vec3_path* pRotation, Behaviour* pBehaviour, UINT nrOffsets, Math::Matrix* pOffsets)
		{
			m_releases.push_back({nrPerIRelease, interval, pRotation, pBehaviour->incrementUsers(), nrOffsets, pOffsets});
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