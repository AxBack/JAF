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

		float m_dispersion { 2.0f };

	public:

		virtual void clear() override
		{
			m_sizes.clear();
			m_colors.clear();
		}

		void setDispersion(float dispersion) { m_dispersion = dispersion; }

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

		virtual void start(BehaviourInfluenced* pItem, const Math::Matrix& offset) override;

		virtual void end(BehaviourInfluenced* pItem) override
		{
			TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
			m_data.push(pData);
		}

		virtual bool update(BehaviourInfluenced* pItem, float time) override;
	};
};