#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"
#include "weighted_value.h"

namespace JAF {

	class BurstBehaviour : public Behaviour
	{
	private:

		struct Release
		{
			int total;
			int nrPerInterval;
			Behaviour* pBehaviour;
			float interval;
		};

		struct ReleaseData
		{
			UINT index;
			float counter;
			int nrParticlesLeft;
		};

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Matrix offset;
			std::vector<ReleaseData> releases;
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		WeightedValue<Math::Vector3> m_position;
		WeightedValue<float> m_size;
		WeightedValue<Math::Color> m_color;

		std::vector<Release> m_releases;

		void updateReleases(UpdateData* pUpdateData, TransformData* pData, BehaviourInfluenced* pItem);

		float m_degrees = { 0 };

	public:

		virtual void clear() override
		{
			m_position.clear();
			m_size.clear();
			m_color.clear();
			m_degrees = 0;

			for(auto& it : m_releases)
				it.pBehaviour->decrementUsers();

			m_releases.clear();
		}

		void setRelease(float degrees) { m_degrees = degrees; }

		void add(int nrParticles, Behaviour* pBehaviour, float interval = -1, int nrPerInterval = -1)
		{
			m_releases.push_back({nrParticles, nrPerInterval == -1 ? nrParticles : nrPerInterval,
								  pBehaviour->incrementUsers(), interval});
		}

		void add(float weight, JAWE::Path<Math::Vector3>* pPosition)
		{
			m_position.add(weight, pPosition);
		}

		void add(float weight, JAWE::Path<float>* pSize)
		{
			m_size.add(weight, pSize);
		}

		void add(float weight, JAWE::Path<Math::Color>* pColor)
		{
			m_color.add(weight, pColor);
		}

		virtual void normalize()
		{
			m_position.normalize();
			m_size.normalize();
			m_color.normalize();
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
};