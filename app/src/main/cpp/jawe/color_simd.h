#pragma once

#include <arm_neon.h>

#include "binary_reader.h"
#include "simd_object.h"
#include "../pch.h"
#include "utils.h"

namespace Math {

#define R 0
#define G 1
#define B 2
#define A 3

struct Color : public SimdObject {
	private:
		float m_data[4] { 0,0,0,0 };

	public:

		Color()
			:Color(0,0,0,0)
		{
		}

		Color(float r, float g, float b, float a)
		{
			m_data[A] = a;
			m_data[R] = r;
			m_data[G] = g;
			m_data[B] = b;
			load();
		}

		float a() const { return m_data[A]; }
		float r() const { return m_data[R]; }
		float g() const { return m_data[G]; }
		float b() const { return m_data[B]; }

		void read(JAWE::IO::BinaryReader *in) {
			m_data[A] = in->read<float>();
			m_data[R] = in->read<float>();
			m_data[R] = in->read<float>();
			m_data[B] = in->read<float>();
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

		Color& operator=(const Color &rhs)
		{
			m_data[A] = rhs.m_data[A];
			m_data[R] = rhs.m_data[R];
			m_data[G] = rhs.m_data[G];
			m_data[B] = rhs.m_data[B];
			//m_simdData = rhs.m_simdData;
			return *this;
		}

		Color operator*(const float scale) const
		{
			if(Utils::SIMD::ready)
			{
				Color v;
				vmulq_n_f32(vld1q_f32(v.m_data), scale);
				return v;
			}
			return {m_data[R] * scale, m_data[G] * scale, m_data[B] * scale, m_data[A] * scale};
		}

		void operator*=(const float rhs)
		{
			if(Utils::SIMD::ready)
				vst1q_f32(m_data, vmulq_n_f32(vld1q_f32(m_data), rhs));
			else
			{
				m_data[A] *= rhs;
				m_data[R] *= rhs;
				m_data[G] *= rhs;
				m_data[B] *= rhs;
			}
		}

		Color operator/(const float scale) const
		{
			return {m_data[R] / scale, m_data[G] / scale, m_data[B] / scale, m_data[A] / scale};
		}

		void operator/=(const float rhs)
		{
			m_data[A] /= rhs;
			m_data[R] /= rhs;
			m_data[G] /= rhs;
			m_data[B] /= rhs;
		}

		Color operator+(const Color &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Color v;
				vst1q_f32(v.m_data, vaddq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			return {m_data[R] + rhs.m_data[R], m_data[G] + rhs.m_data[G],
					m_data[B] + rhs.m_data[B], m_data[A] + rhs.m_data[A]};
		}

		void operator+=(const Color &rhs)
		{
			if(Utils::SIMD::ready)
				vst1q_f32(m_data, vaddq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			else
			{
				m_data[A] += rhs.m_data[A];
				m_data[R] += rhs.m_data[R];
				m_data[G] += rhs.m_data[G];
				m_data[B] += rhs.m_data[B];
			}
		}

		Color operator-(const Color &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Color v;
				vst1q_f32(v.m_data, vsubq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			else
			{
				return {m_data[R] - rhs.m_data[R], m_data[G] - rhs.m_data[G],
						m_data[B] - rhs.m_data[B], m_data[A] - rhs.m_data[A]};
			}
		}

		void operator-=(const Color &rhs)
		{
			if(Utils::SIMD::ready)
				vst1q_f32(m_data, vsubq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			else
			{
				m_data[A] -= rhs.m_data[A];
				m_data[R] -= rhs.m_data[R];
				m_data[G] -= rhs.m_data[G];
				m_data[B] -= rhs.m_data[B];
			}
		}

		Color operator*(const Color &rhs) const
		{
			if(Utils::SIMD::ready)
			{
				Color v;
				vst1q_f32(v.m_data, vmulq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
				return v;
			}
			return {m_data[R] * rhs.m_data[R], m_data[G] * rhs.m_data[G],
					m_data[B] * rhs.m_data[B], m_data[A] * rhs.m_data[A]};
		}

		void operator*=(const Color &rhs)
		{
			if(Utils::SIMD::ready)
				vst1q_f32(m_data, vmulq_f32(vld1q_f32(m_data), vld1q_f32(rhs.m_data)));
			else
			{
				m_data[A] *= rhs.m_data[A];
				m_data[R] *= rhs.m_data[R];
				m_data[G] *= rhs.m_data[G];
				m_data[B] *= rhs.m_data[B];
			}
		}

		Color operator/(const Color &rhs) const {
			return {m_data[R] / rhs.m_data[R], m_data[G] / rhs.m_data[G],
					m_data[B] / rhs.m_data[B], m_data[A] / rhs.m_data[A]};
		}

		void operator/=(const Color &rhs) {
			m_data[R] /= rhs.m_data[R];
			m_data[G] /= rhs.m_data[G];
			m_data[B] /= rhs.m_data[B];
			m_data[A] /= rhs.m_data[A];
		}

		const float *data() const { return &m_data[0]; }
	};

}