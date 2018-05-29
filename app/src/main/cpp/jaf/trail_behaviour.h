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
			JAWE::MATH::Vector3 position;
			JAWE::MATH::Vector3 force;
			float deviation;
			float_vec sizeWeights;
			float_vec colorWeights;
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		WeightedValue<float> m_size;
		WeightedValue<JAWE::MATH::Color> m_color;

		float m_dispersion { 2.0f };
		float m_sizeDeviation = { 0.0f };
		float m_colorDeviation = { 0.0f };

		JAWE::MATH::Vector3 m_gravity { 0, -980, 0};

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
		void setGravity(const JAWE::MATH::Vector3& gravity) { m_gravity = gravity; }

		void add(float weight, JAWE::Path<float>* pSize)
		{
			m_size.add(weight, pSize);
		}

		void add(float weight, JAWE::Path<JAWE::MATH::Color>* pColor)
		{
			m_color.add(weight, pColor);
		}

		virtual void normalize()
		{
			m_size.normalize();
			m_color.normalize();
		}

		virtual void start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
};