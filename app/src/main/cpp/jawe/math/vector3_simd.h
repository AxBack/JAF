#pragma once

#include "../io/binary_reader.h"
#include "../../pch.h"
#include "simd_object.h"
#include "../utils.h"

#include <math.h>
#include <cmath>
#include <arm_neon.h>

namespace JAWE { namespace MATH {

#define X 0
#define Y 1
#define Z 2

struct Vector3 : public MATH::SimdObject {
	private:
		float m_data[4];

	public:

		Vector3()
		 :Vector3(0,0,0)
		{
		}

		Vector3(float x, float y, float z)
		{
			m_data[X] = x;
			m_data[Y] = y;
			m_data[Z] = z;
			m_data[3] = 0;
			load();
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
			load();
		}

		virtual void load() override
		{
			//m_simdData = vld1q_f32(m_data);
		}

		virtual void unload() override
		{
			//vst1q_f32(m_data, m_simdData);
		}

		Vector3& operator=(const Vector3 &rhs) {
			m_data[X] = rhs.m_data[X];
			m_data[Y] = rhs.m_data[Y];
			m_data[Z] = rhs.m_data[Z];
			//m_simdData = rhs.m_simdData;
			return *this;
		}

		bool operator==(const Vector3& rhs)
		{
			unload();
			return m_data[X] == rhs.m_data[X] &&
				   m_data[Y] == rhs.m_data[Y] &&
				   m_data[Z] == rhs.m_data[Z];
		}

		bool operator!=(const Vector3& rhs)
		{
			unload();
			return m_data[X] != rhs.m_data[X] ||
				   m_data[Y] != rhs.m_data[Y] ||
				   m_data[Z] != rhs.m_data[Z];
		}

		Vector3 operator*(const float scale) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
				vst1q_f32(v.m_data, vmulq_n_f32(vld1q_f32(m_data), scale));
				return v;
			}
			return {m_data[X] * scale, m_data[Y] * scale, m_data[Z] * scale};
		}

		void operator*=(const float rhs)
		{
			if(Utils::SIMD::ready)
				vst1q_f32(m_data, vmulq_n_f32(vld1q_f32(m_data), rhs));
			else
			{
				m_data[X] *= rhs;
				m_data[Y] *= rhs;
				m_data[Z] *= rhs;
			}
		}

		Vector3 operator/(const float scale) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
#if defined(__aarch64__)
                vst1q_f32(v.m_data, vdivq_f32(vld1q_f32(m_data), vdupq_n_f32(scale)));
#else
                vst1q_f32(v.m_data, vmulq_f32(vld1q_f32(m_data), vrecpeq_f32(vdupq_n_f32(scale))));
#endif
				return v;
			}
			return {m_data[X] / scale, m_data[Y] / scale, m_data[Z] / scale};
		}

		void operator/=(const float rhs)
		{
			if(Utils::SIMD::ready)
			{
#if defined(__aarch64__)
                vst1q_f32(m_data, vdivq_f32(vld1q_f32(m_data), vdupq_n_f32(rhs)));
#else
                vst1q_f32(m_data, vmulq_f32(vld1q_f32(m_data), vrecpeq_f32(vdupq_n_f32(rhs))));
#endif
			}
			else
			{
				m_data[X] /= rhs;
				m_data[Y] /= rhs;
				m_data[Z] /= rhs;
			}
		}

		Vector3 operator+(const Vector3 &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
				vst1q_f32(v.m_data, vaddq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			return {m_data[X] + rhs.m_data[X], m_data[Y] + rhs.m_data[Y], m_data[Z] + rhs.m_data[Z]};
		}

		void operator+=(const Vector3 &rhs)
		{
			if(Utils::SIMD::ready){
				vst1q_f32(m_data, vaddq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			}
			else
			{
				m_data[X] += rhs.m_data[X];
				m_data[Y] += rhs.m_data[Y];
				m_data[Z] += rhs.m_data[Z];
			}
		}

		Vector3 operator-(const Vector3 &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
				vst1q_f32(v.m_data, vsubq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			return {m_data[X] - rhs.m_data[X], m_data[Y] - rhs.m_data[Y], m_data[Z] - rhs.m_data[Z]};
		}

		void operator-=(const Vector3 &rhs)
		{
			if(Utils::SIMD::ready){
				vst1q_f32(m_data, vsubq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			}
			else
			{
				m_data[X] -= rhs.m_data[X];
				m_data[Y] -= rhs.m_data[Y];
				m_data[Z] -= rhs.m_data[Z];
			}
		}

		Vector3 operator*(const Vector3 &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
				vst1q_f32(v.m_data, vmulq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			return {m_data[X] * rhs.m_data[X], m_data[Y] * rhs.m_data[Y], m_data[Z] * rhs.m_data[Z]};
		}

		void operator*=(const Vector3 &rhs)
		{
			if(Utils::SIMD::ready)
			{
				vst1q_f32(m_data, vmulq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			}
			else
			{
				m_data[X] *= rhs.m_data[X];
				m_data[Y] *= rhs.m_data[Y];
				m_data[Z] *= rhs.m_data[Z];
			}
		}

		Vector3 operator/(const Vector3 &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Vector3 v;
#if defined(__aarch64__)
                vst1q_f32(v.m_data, vdivq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
#else
				vst1q_f32(v.m_data, vmulq_f32(vld1q_f32(m_data), vrecpeq_f32(vld1q_dup_f32(rhs.m_data))));
#endif
				return v;
			}
			return {m_data[X] / rhs.m_data[X], m_data[Y] / rhs.m_data[Y], m_data[Z] / rhs.m_data[Z]};
		}

		void operator/=(const Vector3 &rhs)
		{
			if(Utils::SIMD::ready)
			{
#if defined(__aarch64__)
                vst1q_f32(m_data, vdivq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
#else
			    vst1q_f32(m_data, vmulq_f32(vld1q_f32(m_data), vrecpeq_f32(vld1q_dup_f32(rhs.m_data))));
#endif
			}
			else
			{
				m_data[X] /= rhs.m_data[X];
				m_data[Y] /= rhs.m_data[Y];
				m_data[Z] /= rhs.m_data[Z];
			}
		}

		const float* data() const { return &m_data[0]; }

		float length() const {
			return static_cast<float>(sqrt(lengthSq()));
		}

		float lengthSq() const {
		    if(Utils::SIMD::ready) {
#if defined(__aarch64__)
                float32x4_t v = vld1q_f32(m_data);
                return vaddvq_f32(vmulq_f32(v, v));

#else
                float d[4];
                float32x4_t v = vld1q_f32(m_data);
                vst1q_f32(d, vmulq_f32(v, v));
                return d[0] + d[1] + d[2];
#endif
            }
			return std::abs(m_data[X] * m_data[X] + m_data[Y] * m_data[Y] + m_data[Z] * m_data[Z]);
		}

		void normalize() {
			float l = 1.f / length();
			this->operator*=(l);
		}

		Vector3 cross(const Vector3 &other) const {
			return cross(*this, other);
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
			if(Utils::SIMD::ready)
			{
#if defined(__aarch64__)
			    return vaddvq_f32(vmulq_f32(vld1q_f32(lhs.m_data), vld1q_f32(rhs.m_data)));
#else
                float v[4];
				vst1q_f32(v, vmulq_f32(vld1q_f32(lhs.m_data), vld1q_f32(rhs.m_data)) );
				return v[0] + v[1] + v[2];
#endif
			}
			return lhs.m_data[X] * rhs.m_data[X] + lhs.m_data[Y] * rhs.m_data[Y] + lhs.m_data[Z] * rhs.m_data[Z];
		}
	};
}}