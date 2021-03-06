#pragma once

#if defined(__ARM_NEON)
#include "vector3_simd.h"
#else

#include "../io/binary_reader.h"
#include "../../pch.h"
#include "simd_object.h"

#include <math.h>
#include <cmath>

namespace JAWE { namespace MATH {

#define X 0
#define Y 1
#define Z 2

struct Vector3 : public MATH::SimdObject {
    private:
		float m_data[3] {0,0,0};

    public:

		Vector3()
		{
			memset(m_data, 0, sizeof(m_data));
		}

		Vector3(float x, float y, float z)
		{
			m_data[X] = x;
			m_data[Y] = y;
			m_data[Z] = z;
		}

		float x() const { return m_data[X]; }
		float y() const { return m_data[Y]; }
		float z() const { return m_data[Z]; }

		void x(float v) { m_data[X] = v; }
		void y(float v) { m_data[Y] = v; }
		void z(float v) { m_data[Z] = v; }

		void read(JAWE::IO::BinaryReader* in)
		{
			m_data[X] = in->read<float>();
			m_data[Y] = in->read<float>();
			m_data[Z] = in->read<float>();
		}

		Vector3& operator=(const Vector3 &rhs) {
			m_data[X] = rhs.m_data[X];
			m_data[Y] = rhs.m_data[Y];
			m_data[Z] = rhs.m_data[Z];
			return *this;
		}

		bool operator==(const Vector3& rhs) const
		{
			return m_data[X] == rhs.m_data[X] &&
					m_data[Y] == rhs.m_data[Y] &&
					m_data[Z] == rhs.m_data[Z];
		}

		bool operator!=(const Vector3& rhs) const
		{
			return m_data[X] != rhs.m_data[X] ||
				   m_data[Y] != rhs.m_data[Y] ||
				   m_data[Z] != rhs.m_data[Z];
		}

		Vector3 operator*(const float scale) const
		{
			return {m_data[X] * scale, m_data[Y] * scale, m_data[Z] * scale};
		}

		void operator*=(const float rhs)
		{
			m_data[X] *= rhs;
			m_data[Y] *= rhs;
			m_data[Z] *= rhs;
		}

		Vector3 operator/(const float scale) const {
			return {m_data[X] / scale, m_data[Y] / scale, m_data[Z] / scale};
		}

		void operator/=(const float rhs) {
			m_data[X] /= rhs;
			m_data[Y] /= rhs;
			m_data[Z] /= rhs;
		}

		Vector3 operator+(const Vector3 &rhs) const {
			return {m_data[X] + rhs.m_data[X], m_data[Y] + rhs.m_data[Y], m_data[Z] + rhs.m_data[Z]};
		}

		void operator+=(const Vector3 &rhs) {
			m_data[X] += rhs.m_data[X];
			m_data[Y] += rhs.m_data[Y];
			m_data[Z] += rhs.m_data[Z];
		}

		Vector3 operator-(const Vector3 &rhs) const {
			return {m_data[X] - rhs.m_data[X], m_data[Y] - rhs.m_data[Y], m_data[Z] - rhs.m_data[Z]};
		}

		void operator-=(const Vector3 &rhs) {
			m_data[X] -= rhs.m_data[X];
			m_data[Y] -= rhs.m_data[Y];
			m_data[Z] -= rhs.m_data[Z];
		}

		Vector3 operator*(const Vector3 &rhs) const {
			return {m_data[X] * rhs.m_data[X], m_data[Y] * rhs.m_data[Y], m_data[Z] * rhs.m_data[Z]};
		}

		void operator*=(const Vector3 &rhs) {
			m_data[X] *= rhs.m_data[X];
			m_data[Y] *= rhs.m_data[Y];
			m_data[Z] *= rhs.m_data[Z];
		}

		Vector3 operator/(const Vector3 &rhs) const {
			return {m_data[X] / rhs.m_data[X], m_data[Y] / rhs.m_data[Y], m_data[Z] / rhs.m_data[Z]};
		}

		void operator/=(const Vector3 &rhs) {
			m_data[X] /= rhs.m_data[X];
			m_data[Y] /= rhs.m_data[Y];
			m_data[Z] /= rhs.m_data[Z];
		}

		const float* data() const { return &m_data[0]; }

		float length() const {
			return static_cast<float>(sqrt(lengthSq()));
		}

		float lengthSq() const {
			return std::abs(m_data[X] * m_data[X] + m_data[Y] * m_data[Y] + m_data[Z] * m_data[Z]);
		}

		void normalize() {
			float l = 1.f / length();
			m_data[X] *= l;
			m_data[Y] *= l;
			m_data[Z] *= l;
		}

		Vector3 cross(const Vector3 &other) const {
			return {
					m_data[Y] * other.m_data[Z] - m_data[Z] * other.m_data[Y],
					m_data[Z] * other.m_data[X] - m_data[X] * other.m_data[Z],
					m_data[X] * other.m_data[Y] - m_data[Y] * other.m_data[X]
			};
		}

		static Vector3 cross(const Vector3& lhs, const Vector3& rhs)
		{
			return {
					lhs.m_data[Y] * rhs.m_data[Z] - lhs.m_data[Z] * rhs.m_data[Y],
					lhs.m_data[Z] * rhs.m_data[X] - lhs.m_data[X] * rhs.m_data[Z],
					lhs.m_data[X] * rhs.m_data[Y] - lhs.m_data[Y] * rhs.m_data[X]
			};
		}

		static float dot(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.m_data[X] * rhs.m_data[X] + lhs.m_data[Y] * rhs.m_data[Y] + lhs.m_data[Z] * rhs.m_data[Z];
		}
	};
}}

#endif