#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"
#include "weighted_value.h"

namespace JAF {

	class TrailBehaviour : public Behaviour
	{
	private:

		typedef std::vector<float> float_vec;

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Vector3 position;
			Math::Vector3 force;
			float deviation;
			float_vec sizeWeights;
			float_vec colorWeights;
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		WeightedValue<float> m_size;
		WeightedValue<Math::Color> m_color;

		float m_dispersion { 2.0f };
		float m_sizeDeviation = { 0.0f };
		float m_colorDeviation = { 0.0f };

		Math::Vector3 m_gravity { 0, -980, 0};

	public:

		virtual void clear() override
		{
			m_size.clear();
			m_color.clear();
			m_dispersion = 0.0f;
			m_sizeDeviation = 0.0f;
			m_colorDeviation = 0.0f;
		}

		void setDispersion(float dispersion) { m_dispersion = dispersion; }
		void setDeviation(float size, float color)
		{
			m_sizeDeviation = size;
			m_colorDeviation = color;
		}
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