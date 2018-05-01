#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"
#include "weighted_value.h"

namespace JAF {

	class TrailBehaviour : public Behaviour
	{
	private:

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Vector3 position;
			Math::Vector3 force;
			float time;
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		WeightedValue<float> m_size;
		WeightedValue<Math::Color> m_color;

		float m_dispersion { 2.0f };

		Math::Vector3 m_gravity { 0, -980, 0};

	public:

		virtual void clear() override
		{
			m_size.clear();
			m_color.clear();
		}

		void setDispersion(float dispersion) { m_dispersion = dispersion; }
		void setGravity(const Math::Vector3& gravity) { m_gravity = gravity; }

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