#include "burst_behaviour.h"

namespace JAF {

	void BurstBehaviour::start(BehaviourInfluenced* pItem, const Math::Matrix& offset)
	{
		TransformData* pData = m_data.pop();

		float x = JAWE::Random::randf(-180.0f, 180.0f);
		float z = JAWE::Random::randf(-180.0f, 180.0f);
		pData->offset = Math::Matrix::multiply(offset, Math::Matrix::setRotate(x,0,z));

		pItem->setData(pData);
	}

	bool BurstBehaviour::update(UpdateData* pUpdateData, BehaviourInfluenced* pItem, float time)
	{
		if(time >= m_timeLimit)
			return false;

		float delta = time / m_timeLimit;

		TransformData* pData = reinterpret_cast<TransformData*>(pItem->getData());
		Math::Vector3 p = pData->offset.transform(PathBehaviour::update<Math::Vector3>({0,0,0}, m_positions, delta), 1);

		pItem->setPosition(p);
		pItem->setRadius(PathBehaviour::update<float>(0.0f, m_sizes, delta));
		pItem->setColor(PathBehaviour::update<Math::Color>({0,0,0,0}, m_colors, delta));

		return true;
	}
}