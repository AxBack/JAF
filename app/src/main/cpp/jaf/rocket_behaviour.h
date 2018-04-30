#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	class RocketBehaviour : public PathBehaviour
	{
	public:

		enum OffsetType { POINT, LINE, CIRCLE };

	private:

		struct Burst
		{
			UINT nr;
			Behaviour* pBehaviour;
		};

		struct Trail
		{
			float interval;
			float time;
			Behaviour* pBehaviour;
		};

		typedef std::vector<Burst> burst_vec;
		typedef std::vector<Trail> trail_vec;

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Vector3 offset {0,0,0};
			Math::Vector3 factors {1,1,1};
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;

		burst_vec m_bursts;
		trail_vec m_trails;

		OffsetType m_offsetType { POINT };
		Math::Vector3 m_offset { 0,0,0 };
		float m_tag { 0 };
		UINT m_nrReleased { 0 };

		void burst(UpdateData* pUpdateData, Burst& burst, const Math::Matrix& offset);

	public:

		virtual void clear() override
		{
			m_positions.clear();
			m_nrReleased = 0;

			for(auto& it : m_bursts)
				it.pBehaviour->decrementUsers();
			m_bursts.clear();

			for(auto& it : m_trails)
				it.pBehaviour->decrementUsers();
			m_trails.clear();
		}

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

		void add(UINT nr, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_bursts.push_back({nr, pBehaviour});
		}

		void add(float interval, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_trails.push_back({ interval, interval, pBehaviour });
		}

		void setOffset(OffsetType type, const Math::Vector3& v, float t)
		{
			m_offsetType = type;
			m_offset = v;
			m_tag = t;
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			if(pData != nullptr)
				m_data.push(pData);
		}

		virtual void normalize() override
		{
			PathBehaviour::normalize(m_positions);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
};