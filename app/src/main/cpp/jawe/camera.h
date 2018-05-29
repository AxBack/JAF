#pragma once

#include <mutex>
#include "math/matrix.h"
#include "path.h"

namespace JAWE {

	class Camera
	{
	private:

		typedef MATH::Matrix Matrix;
		typedef MATH::Vector3 Vector3;

		bool        m_vpDirty { true };
		Matrix		m_viewProjection;

		float 		m_zMin;
		float 		m_zMax;

		Vector3 	m_position { 0,0,0 };
		Vector3 	m_at { 0,0,1};
		Vector3 	m_forward { 0,0,1};
		Vector3 	m_right { 1,0,0 };
		Vector3		m_up { 0,1,0};

		float 		m_aspectRatio;

		Matrix      m_view;
		Matrix      m_projection;

	public:

		Camera(float zMin, float zMax)
				: m_zMin(zMin)
				, m_zMax(zMax)
		{
		}


		virtual ~Camera()
		{
		}

		void update()
		{
			if(m_vpDirty)
			{
                m_vpDirty = false;
				m_viewProjection = m_projection * m_view;
				m_forward = m_at - m_position;
				m_forward.normalize();
				m_right = m_up.cross(m_forward);
			}
		}

		const Matrix& getViewProjection() const { return m_viewProjection; }
		const Vector3& getPosition() const { return m_position; }
		const Vector3& getForward() const { return m_forward; }
		const Vector3& getUp() const { return m_up; }
		const Vector3& getRight() const { return m_right; }
		float getAspectRatio() const { return m_aspectRatio; }

        void updateView(const Vector3& position, const Vector3& at, const Vector3& up)
        {
            m_position = position;
			m_up = up;
			m_at = at;
            Matrix::lookAt(m_view, m_position, at, up);
            m_vpDirty = true;
        }

		void setProjection(float w, float h)
		{
			m_aspectRatio = w / h;
			Matrix::perspective(m_projection, 90.0f, m_aspectRatio, m_zMin, m_zMax);
			m_vpDirty = true;
		}

		void setOrtho(float w, float h)
		{
			m_aspectRatio = w / h;
			Matrix::ortho(m_projection, -w*0.5f, w*0.5f, -h*0.5f, h*0.5f, m_zMin, m_zMax);
		}
	};

};
