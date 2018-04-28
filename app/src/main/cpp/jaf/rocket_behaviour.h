#pragma once

#include "behaviour.h"

namespace JAF {

	class RocketBehaviour : public PathBehaviour
	{
	private:

		struct TransformData : public BehaviourInfluenced::Data
		{
			Math::Vector3 offset {0,0,0};
			Math::Vector3 factors {1,1,1};
		};

		typedef JAWE::Bank<TransformData*> data_bank;
		data_bank m_data {[](){return new TransformData(); }, [](TransformData* p) { delete p; }};

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;

	public:

		virtual void clear() override
		{
			m_positions.clear();
		}

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override
		{
			TransformData* pData = m_data.pop();

			pData->offset = offset.transform({0,0,0}, 1);
			pData->factors = {1,1,1};

			pItem->setData(pData);
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