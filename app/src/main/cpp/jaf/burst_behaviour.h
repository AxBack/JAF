#pragma once

#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	class BurstBehaviour : public PathBehaviour
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

		std::vector<std::pair<float, vec3_path_ptr>> m_positions;
		std::vector<std::pair<float, float_path_ptr>> m_sizes;
		std::vector<std::pair<float, color_path_ptr>> m_colors;

		std::vector<Release> m_releases;

		void updateReleases(UpdateData* pUpdateData, TransformData* pData, BehaviourInfluenced* pItem);

		float m_degrees = { 0 };

	public:

		virtual void clear() override
		{
			m_positions.clear();
			m_sizes.clear();
			m_colors.clear();
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

		void add(float weight, vec3_path_ptr pPosition)
		{
			m_positions.push_back(std::make_pair(weight, pPosition));
		}

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
			PathBehaviour::normalize(m_positions);
			PathBehaviour::normalize(m_sizes);
			PathBehaviour::normalize(m_colors);
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