#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"
#include "weighted_value.h"

namespace JAF {

	class RocketBehaviour : public Behaviour
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
			Behaviour* pBehaviour;
		};

		typedef std::vector<Burst> burst_vec;
		typedef std::vector<Trail> trail_vec;
		typedef std::vector<float> float_vec;

		struct TransformData : public BehaviourInfluenced::Data
		{
			JAWE::MATH::Vector3 offset {0,0,0};
			JAWE::MATH::Vector3 factors {1,1,1};
			float deviation = 0.0f;
			float_vec weights;
			float_vec counters;
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		WeightedValue<JAWE::MATH::Vector3> m_position;
		float m_positionDeviation = {0.0f};

		burst_vec m_bursts;
		trail_vec m_trails;

		OffsetType m_offsetType { POINT };
		JAWE::MATH::Vector3 m_offset { 0,0,0 };
		float m_tag { 0 };
		UINT m_nrReleased { 0 };


	public:

		virtual void clear() override
		{
			m_position.clear();
			m_positionDeviation = 0.0f;
			m_nrReleased = 0;

			for(auto& it : m_bursts)
				it.pBehaviour->decrementUsers();
			m_bursts.clear();

			for(auto& it : m_trails)
				it.pBehaviour->decrementUsers();
			m_trails.clear();
		}

		void add(float weight, JAWE::Path<JAWE::MATH::Vector3>* pPosition)
		{
			m_position.add(weight, pPosition);
		}

		void setPositionDeviation(float deviation) { m_positionDeviation = deviation; }

		void add(UINT nr, Behaviour* pBehaviour)
		{
			m_bursts.push_back({nr, pBehaviour->incrementUsers()});
		}

		void add(float interval, Behaviour* pBehaviour)
		{
			pBehaviour->incrementUsers();
			m_trails.push_back({ interval, pBehaviour });
		}

		void setOffset(OffsetType type, const JAWE::MATH::Vector3& v, float t)
		{
			m_offsetType = type;
			m_offset = v;
			m_tag = t;
		}

		virtual void start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			pData->counters.clear();
			pData->weights.clear();
			if(pData != nullptr)
				m_data.push(pData);
		}

		virtual void normalize()
		{
			m_position.normalize();
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
};