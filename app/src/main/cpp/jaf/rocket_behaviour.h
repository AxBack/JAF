#pragma once

#include "behaviour.h"

namespace JAF {

	class RocketBehaviour : public PathBehaviour
	{
	public:

		enum OffsetType { POINT, LINE, CIRCLE };

	private:

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Vector3 offset {0,0,0};
			Math::Vector3 factors {1,1,1};
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;


		OffsetType m_offsetType { POINT };
		Math::Vector3 m_offset { 0,0,0 };
		float m_tag { 0 };
		UINT m_nrReleased { 0 };

	public:

		virtual void clear() override
		{
			m_positions.clear();
			m_nrReleased = 0;
		}

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

		void setOffset(OffsetType type, const Math::Vector3& v, float t)
		{
			m_offsetType = type;
			m_offset = v;
			m_tag = t;
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override
		{
			TransformData* pData = m_data.pop();
			pData->factors = {1,1,1};

			Math::Vector3 p = m_offset;
			switch(m_offsetType)
			{
				case LINE:
					p.normalize();
					p = m_offset - (p * m_tag * static_cast<float>(m_nrReleased));
					break;
				case CIRCLE:
					p = Math::Matrix::transform(Math::Matrix::setRotate(0, static_cast<float>(m_nrReleased) * m_tag, 0), p, 0.0f);
					pData->factors = p;
					pData->factors.normalize();
					pData->factors.y(1);
					break;
			}

			pData->offset = offset.transform(p);

			pItem->setData(pData);
			++m_nrReleased;
		}

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

		virtual bool update(BehaviourInfluenced* pItem, float time) override
		{
			if(time >= m_timeLimit)
				return false;

			float delta = time / m_timeLimit;

			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			Math::Vector3 p = pData->offset + (PathBehaviour::update<Math::Vector3>({0,0,0}, m_positions, delta) * pData->factors);

			pItem->setPosition(p);
			pItem->setRadius(0);

			return true;
		}
	};
};