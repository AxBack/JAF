#pragma once

#if defined(__ARM_NEON)
#include "quaternion_simd.h"
#else
#include <math.h>
#include "../../pch.h"
#include "vector3.h"

namespace JAWE { namespace MATH {

#define X 0
#define Y 1
#define Z 2
#define W 3

    struct Quaternion {
	private:
        float m_data[4] { 0,0,0,1};

	public:

		Quaternion()
		{
		}

		Quaternion(float x, float y, float z, float w)
		{
			m_data[X] = x;
			m_data[Y] = y;
			m_data[Z] = z;
			m_data[W] = w;
		}

		bool isIdentity() { return m_data[X] == 0 && m_data[Y] == 0 && m_data[Z] == 0 && m_data[W] == 1; }

		bool operator==(const Quaternion& rhs) const
		{
			return m_data[X] == rhs.m_data[X] &&
				   m_data[Y] == rhs.m_data[Y] &&
				   m_data[Z] == rhs.m_data[Z] &&
				   m_data[W] == rhs.m_data[W];
		}

        virtual Quaternion operator*(const Quaternion& rhs) const
        {
            float x1 = m_data[X];
            float y1 = m_data[Y];
            float z1 = m_data[Z];
            float w1 = m_data[W];

            float x2 = rhs.m_data[X];
            float y2 = rhs.m_data[Y];
            float z2 = rhs.m_data[Z];
            float w2 = rhs.m_data[W];

            Quaternion q;
            q.m_data[X] = x1*w2 + y1*z2 - z1*y2 + w1*x2;
            q.m_data[Y] = x1*z2 + y1*w2 + z1*x2 + w1*y2;
            q.m_data[Z] = x1*y2 - y1*x2 + z1*w2 + w1*z2;
            q.m_data[W] = x1*x2 - y1*y2 - z1*z2 + w1*w2;
            return std::move(q);
        }

        virtual void operator*=(const Quaternion& rhs)
        {
            float x1 = m_data[X];
            float y1 = m_data[Y];
            float z1 = m_data[Z];
            float w1 = m_data[W];

            float x2 = rhs.m_data[X];
            float y2 = rhs.m_data[Y];
            float z2 = rhs.m_data[Z];
            float w2 = rhs.m_data[W];

			m_data[X] = x1*w2 + y1*z2 - z1*y2 + w1*x2;
			m_data[Y] = x1*z2 + y1*w2 + z1*x2 + w1*y2;
			m_data[Z] = x1*y2 - y1*x2 + z1*w2 + w1*z2;
			m_data[W] = x1*x2 - y1*y2 - z1*z2 + w1*w2;
        }

		virtual Vector3 operator*(const Vector3& rhs)
		{
			Vector3 v(m_data[X], m_data[Y], m_data[Z]);
			Vector3 r = rhs * (Vector3::dot(rhs, v) * 2.0f);
			return  rhs * (Vector3::dot(rhs, v) * 2.0f)
					+ v * (m_data[W]*m_data[W] - Vector3::dot(rhs, rhs))
					+ Vector3::cross(rhs, v) *(2.0f * m_data[W]); //TODO: does this work?
		}

		virtual Quaternion operator+(const Quaternion& rhs)
		{
			return {m_data[X] + rhs.m_data[X],
					m_data[Y] + rhs.m_data[Y],
					m_data[Z] + rhs.m_data[Z],
					m_data[W] + rhs.m_data[W]};
		}

		virtual Quaternion operator-(const Quaternion& rhs)
		{
			return {m_data[X] - rhs.m_data[X],
					m_data[Y] - rhs.m_data[Y],
					m_data[Z] - rhs.m_data[Z],
					m_data[W] - rhs.m_data[W]};
		}

		virtual Quaternion operator-() const
		{
			return {-m_data[X], -m_data[Y], -m_data[Z], -m_data[W]};
		}

		virtual Quaternion operator*(const float rhs) const
		{
			return {m_data[X] * rhs,
					m_data[Y] * rhs,
					m_data[Z] * rhs,
					m_data[W] * rhs};
		}

		virtual Quaternion operator/(const float rhs) const
		{
			return {m_data[X] / rhs,
					m_data[Y] / rhs,
					m_data[Z] / rhs,
					m_data[W] / rhs};
		}

		void normalize()
		{
			float n = 1.0f / length();
			m_data[X] *= n;
			m_data[Y] *= n;
			m_data[Z] *= n;
			m_data[W] *= n;
		}

		float lengthSq() const { return m_data[X]*m_data[X] + m_data[Y]*m_data[Y] + m_data[Z]*m_data[Z] + m_data[W]*m_data[W]; }
		float length() const { return sqrtf(lengthSq()); }

        const float x() const { return m_data[X]; }
        const float y() const { return m_data[Y]; }
        const float z() const { return m_data[Z]; }
        const float w() const { return m_data[W]; }

		void x(float x) { m_data[X] = x;}
		void y(float y) { m_data[Y] = y;}
		void z(float z) { m_data[Z] = z;}
		void w(float w) { m_data[W] = w;}

        const float* data() const { return m_data; }

		static Quaternion identity() { return Quaternion(0,0,0,1); }

        static Quaternion fromEulerAngles(float x, float y, float z)
        {
			x = _to_radians(x);
			y = _to_radians(y);
			z = _to_radians(z);

            float cx = cosf(x * 0.5f);
            float sx = sinf(x * 0.5f);
            float cy = cosf(y * 0.5f);
            float sy = sinf(y * 0.5f);
            float cz = cosf(z * 0.5f);
            float sz = sinf(z * 0.5f);

            Quaternion q;
            q.m_data[X] = sx*cy*cz - cx*sy*sz;
            q.m_data[Y] = cx*sy*cz + sx*cy*sz;
            q.m_data[Z] = cx*cy*sz - sx*sy*cz;
            q.m_data[W] = cx*cy*cz + sx*sy*sz;
            return std::move(q);
        }

		static Quaternion fromRotationVector(float x, float y, float z)
		{
			Quaternion q = {x,y,z,0};
			q.m_data[W] = 1 - x*x - y*y - z*z;
			q.m_data[W] = (q.m_data[W] > 0) ? sqrtf(q.m_data[W]) : 0;
			return q;
		}

        static Quaternion fromAxisAngle(float x, float y, float z, float w)
        {
            return fromAxisAngle(Vector3{x,y,z}, w);
        }

        static Quaternion fromAxisAngle(Vector3 axis, float degrees)
        {
			degrees = _to_radians(degrees);
            float d = sinf(degrees * 0.5f);
            axis *= d;

            Quaternion q;
            q.m_data[X] = axis.x();
            q.m_data[Y] = axis.y();
            q.m_data[Z] = axis.z();
            q.m_data[W] = cosf(degrees * 0.5f);
            return std::move(q);
        }

		static Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float dt)
		{
			Quaternion r = (q1 * (1.0f - dt)) + (q2 * dt);
			r.normalize();
			return std::move(r);
		}

		static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float dt)
		{
			Quaternion q3;
			float d = dot(q1, q2);

			if(d < 0)
			{
				d -= d;
				q3 = -q2;
			}
			else
				q3 = q2;

			if(d < 0.95f)
			{
				float angle = acosf(d);
				return (q1*sinf(angle*(1.0f-dt)) + q3*sinf(angle*dt))/sinf(angle);
			}

			return lerp(q1,q3,dt);
		}

		static float dot(const Quaternion& q1, const Quaternion& q2)
		{
			return q1.x()*q2.x() + q1.y()*q2.y() + q1.z()*q2.z() + q1.w()*q2.w();
		}

		static Quaternion rotationBetweenNormals(const Vector3& n1, const Vector3& n2)
		{
			float a = Vector3::dot(n1, n2);
			Vector3 axis;
			if (a < -1 + 0.001f)
			{
				axis = Vector3::cross({0,0,1}, n1);
				if (axis.lengthSq() < 0.01f)
					axis = Vector3::cross({1,0,0}, n1);

				axis.normalize();
				return {axis.x(), axis.y(), axis.z(), _to_radians(180.0f)};
			}

			axis = Vector3::cross(n1, n2);
			float s = sqrtf((1+a)*2);
			float invs = 1 / s;

			Quaternion q ={axis.x() * invs, axis.y() * invs, axis.z() * invs, s * 0.5f};
			q.normalize();
			return std::move(q);
		}
    };
}}

#include "matrix.h"

#endif