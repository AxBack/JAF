#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"
#include "weighted_value.h"
#include "particle.h"

namespace JAF {

	class BurstBehaviour : public Behaviour
	{
	protected:

		typedef std::vector<float> float_vec;
		struct Data : public BehaviourInfluenced::Data
		{
			JAWE::MATH::Matrix offset;
			float_vec positionWeights;

			JAWE::MATH::Vector3 position;
			JAWE::MATH::Vector3 force;

			float deviation;
			float_vec sizeWeights;
			float_vec colorWeights;
		};

	private:

		typedef JAWE::Bank<Data*> data_bank;
		data_bank m_data {[this](){ return new Data(); }, [](Data* p) { delete p; }};

		WeightedValue<JAWE::MATH::Vector3> m_position;
		WeightedValue<float> m_size;
		WeightedValue<JAWE::MATH::Color> m_color;

		JAWE::MATH::Vector3 m_gravity { 0,0,0 };

		JAWE::MATH::Vector3 m_releaseRotation { 180,180,180 };

		float m_positionDeviation { 0.0f };
		float m_sizeDeviation = { 0.0f };
		float m_colorDeviation = { 0.0f };

		virtual JAWE::MATH::Matrix calculateOffset(const JAWE::MATH::Matrix& transform)
		{
			float x = m_releaseRotation.x();
			float y = m_releaseRotation.y();
			float z = m_releaseRotation.z();

			x = JAWE::Random::randf(-x, x);
			y = JAWE::Random::randf(-y, y);
			z = JAWE::Random::randf(-z, z);

			return JAWE::MATH::Matrix::multiply(transform, JAWE::MATH::Matrix::setRotate(x,y,z) );
		}

		Data* getData()
		{
			Data* pData = m_data.pop();
			pData->positionWeights.clear();
			return pData;
		}

	public:

		virtual void clear() override
		{
			m_position.clear();
			m_size.clear();
			m_color.clear();
			m_positionDeviation = 0.0f;
			m_sizeDeviation = 0.0f;
			m_colorDeviation = 0.0f;
		}

		void setGravity(const JAWE::MATH::Vector3& gravity){ m_gravity = gravity;  }

		void setReleaseRotation(const JAWE::MATH::Vector3& rot) { m_releaseRotation = rot; }

		void setDeviation(float position, float size, float color)
		{
			m_positionDeviation = position;
			m_sizeDeviation = size;
			m_colorDeviation = color;
		}

		void add(float weight, JAWE::Path<JAWE::MATH::Vector3>* pPosition)
		{
			m_position.add(weight, pPosition);
		}

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
			m_position.normalize();
			m_size.normalize();
			m_color.normalize();
		}

		virtual void start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			Data* pData = reinterpret_cast<Data*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time) override;
	};
};