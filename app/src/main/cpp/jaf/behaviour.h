#pragma once

#include <random>
#include "../jawe/math/color.h"
#include "../jawe/random.h"
#include "../jawe/math/matrix.h"

namespace JAF {

    class BehaviourInfluenced
    {
	public:

		struct Data
		{
		};

	private:

		Data* m_pData;

    public:

		virtual JAWE::MATH::Matrix calculateTransform() const = 0;

		void setData(Data* pData) { m_pData = pData; }
		Data* getData() { return m_pData; }

        virtual void setPosition(const JAWE::MATH::Vector3& position) = 0;
        virtual void setRadius(const float size) = 0;
        virtual void setColor(const JAWE::MATH::Color& color) = 0;
    };

	class Behaviour;
	class UpdateData;

	class BehaviourListener
	{
	public:

		virtual void onNotActive(Behaviour* pBehaviour) = 0;
	};

	class Behaviour
	{
	protected:

		BehaviourListener* m_pListener { nullptr };

		int m_nrUsers { 0 };
		float m_timeLimit { 0 };
		float m_allowedDeviation { 0 };

	public:

		void setListener(BehaviourListener* pListener) { m_pListener = pListener; }

		virtual void init(float time, float allowedDeviation = 0.0f)
		{
			clear();
			m_timeLimit = time;
			m_allowedDeviation = allowedDeviation;
		}

		virtual void clear() {m_pListener = nullptr; }

		Behaviour* incrementUsers() { ++m_nrUsers;  return this; }
		void decrementUsers()
		{
			--m_nrUsers;
			if(m_pListener && m_nrUsers <= 0)
			{
				m_pListener->onNotActive(this);
				clear();
			}
		}

		virtual void start(BehaviourInfluenced* pItem, const JAWE::MATH::Matrix& offset) = 0;
		virtual void end(BehaviourInfluenced* pItem) = 0;
		virtual bool update(UpdateData* pData, BehaviourInfluenced* pItem, float dt) = 0;
	};
}
