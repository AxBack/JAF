#include "burst_behaviour.h"
#include "particle.h"
#include "update_data.h"

namespace JAF {

	void BurstBehaviour::start(BehaviourInfluenced* pItem, const Math::Matrix& offset)
	{
		Particle* pParticle = dynamic_cast<Particle*>(pItem);
		if(pParticle == nullptr)
			return;

		TransformData* pData = m_data.pop();

		if(m_degrees > 0.0f)
		{
			float x = JAWE::Random::randf(-m_degrees, m_degrees);
			float z = JAWE::Random::randf(-m_degrees, m_degrees);
			pData->offset = Math::Matrix::multiply(offset, Math::Matrix::setRotate(x, 0, z));
		}
		else
			pData->offset = offset;

		for(UINT i=0; i<m_releases.size(); ++i)
		{
			pData->releases.push_back({i, m_releases[i].interval, m_releases[i].total});
		}

		pParticle->fire(this);
		pItem->setData(pData);
		pItem->setPosition(offset.transform({0,0,0}, 1));
	}

	bool BurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(time >= m_timeLimit)
			return false;

		float delta = time / m_timeLimit;

		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		Math::Vector3 p = pData->offset.transform(m_position.update({0,0,0}, delta), 1);

		pItem->setPosition(p);
		pItem->setRadius(m_size.update(0.0f, delta));
		pItem->setColor(m_color.update({0,0,0,0}, delta));

		updateReleases(pUpdateData, pData, pItem);

		return true;
	}

	void BurstBehaviour::updateReleases(UpdateData* pUpdateData, TransformData* pData, BehaviourInfluenced* pItem)
	{
		for(auto it = pData->releases.begin(); it != pData->releases.end();)
		{
			if((it->counter -= pUpdateData->dt) <= 0.0f)
			{
				const Release& release = m_releases[it->index];
				it->counter += release.interval;

				Math::Matrix offset = pItem->calculateTransform();

				int nr = std::min(release.nrPerInterval, it->nrParticlesLeft);
				for(int i=0; i<nr; ++i)
				{
					Particle* p = pUpdateData->pUpdater->fireParticle();
					release.pBehaviour->start(p, offset);
				}

				it->nrParticlesLeft -= nr;

				if(it->nrParticlesLeft <= 0)
				{
					it = pData->releases.erase(it);
					continue;
				}
			}

			++it;
		}
	}
}