#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	class TrailBehaviour : public PathBehaviour
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

		std::vector<std::pair<float, float_path_ptr>> m_sizes;
		std::vector<std::pair<float, color_path_ptr>> m_colors;

	public:

		void add(float weight, float_path_ptr pSize)
		{
			m_sizes.push_back(std::make_pair(weight, pSize));
		}

		void add(float weight, color_path_ptr pColor)
		{
			m_colors.push_back(std::make_pair(weight, pColor));
		}

		virtual void normalize() override
		{
			PathBehaviour::normalize(m_sizes);
			PathBehaviour::normalize(m_colors);
		}

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override
		{
			PathBehaviour::start(pItem, offset);

			TransformData* pData = m_data.pop();

			Math::Vector3 dir {JAWE::Random::randf(-1.0f, 1.0f), 1, JAWE::Random::randf(-1.0f, 1.0f)};
			dir.normalize();
			dir *= 50.0f;
			pData->force = offset.transform(dir, 0.0f);
			pData->position = offset.transform({0,0,0});
			pData->time = 0.0f;
			pItem->setData(pData);
		}

		virtual void end(BehaviourInfluenced* pItem) override
		{
			PathBehaviour::end(pItem);

			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(BehaviourInfluenced* pItem, float time) override
		{
			if(time >= m_timeLimit)
				return false;

			float delta = time / m_timeLimit;

			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			float dt  = time - pData->time;
			pData->time = time;

			pData->force += (pData->force * -dt) + Math::Vector3(0, -980 ,0) * dt;
			pData->position += pData->force * dt;

			pItem->setPosition(pData->position);
			pItem->setRadius(PathBehaviour::update<float>(0.0f, m_sizes, delta));
			pItem->setColor(PathBehaviour::update<Math::Color>({0,0,0,0}, m_colors, delta));

			return true;
		}
	};
};