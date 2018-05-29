#pragma once

#include <android/sensor.h>
#include "math/vector3.h"
#include "counter.h"

namespace JAWE {

	class Sensor
	{
	private:

		int m_id { -1 };

		Counter m_counter;
		bool m_active { false };

		MATH::Vector3 m_rotation { 0,0,0 };
		MATH::Vector3 m_delta { 0,0,0 };

		ASensorManager* m_pSensorManager { nullptr };
		const ASensor* m_pGyroscope { nullptr };
		ASensorEventQueue* m_pEventQueue { nullptr };
		ALooper* m_pLooper { nullptr };

	public:

		virtual ~Sensor()
		{
			pause();
		}

		bool init(int id)
		{
			m_id = id;
			m_pSensorManager = ASensorManager_getInstance();
			m_pGyroscope = ASensorManager_getDefaultSensor(m_pSensorManager, ASENSOR_TYPE_GYROSCOPE);
			m_pLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
			m_pEventQueue = ASensorManager_createEventQueue(m_pSensorManager, m_pLooper, id, NULL, NULL);
			return true;
		}

		bool active() const { return m_active; }

		void resume()
		{
			if(m_active)
				return;

			m_active = true;
			ASensorEventQueue_enableSensor(m_pEventQueue, m_pGyroscope);
			ASensorEventQueue_setEventRate(m_pEventQueue, m_pGyroscope, 10000);
			m_rotation = {0,0,0};
			m_counter.step();
			_logd("Sensor::Resumed");
		}

		void pause()
		{
			if(!m_active)
				return;

			m_active = false;
			ASensorEventQueue_disableSensor(m_pEventQueue, m_pGyroscope);
			m_rotation = {0,0,0};
			_logd("Sensor::Paused");
		}

		void update()
		{
			if(!m_active)
				return;

			float dt = m_counter.step();

			if(ALooper_pollAll(0, NULL, NULL, NULL) != m_id)
				return;

			m_delta = {0,0,0};

			ASensorEvent event;
			while(ASensorEventQueue_getEvents(m_pEventQueue, &event, 1) > 0)
			{
				m_delta += MATH::Vector3{
						_to_degrees(event.vector.x),
						_to_degrees(event.vector.y),
						_to_degrees(event.vector.z)
				} * dt;
			}

			m_rotation += m_delta;
		}

		MATH::Vector3 getRotation() const { return m_rotation; }
		MATH::Vector3 getDelta() const { return m_delta; }

	};
};
