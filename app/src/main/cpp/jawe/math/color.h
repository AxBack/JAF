#pragma once

#if defined(__ARM_NEON)
#include "color_simd.h"
#else

#include "../io/binary_reader.h"
#include "simd_object.h"

namespace JAWE { namespace MATH {

#define R 0
#define G 1
#define B 2
#define A 3

struct Color : public SimdObject {
	private:
		float m_data[4] { 0,0,0,0 };

	public:

        Color()
        {
        }

        Color(float r, float g, float b, float a)
        {
            m_data[A] = a;
            m_data[R] = r;
            m_data[G] = g;
            m_data[B] = b;
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
		}

		Color &operator=(const Color &rhs) {
			m_data[A] = rhs.m_data[A];
			m_data[R] = rhs.m_data[R];
			m_data[G] = rhs.m_data[G];
			m_data[B] = rhs.m_data[B];
			return *this;
		}

		Color operator*(const float scale) const {
			return {m_data[R] * scale, m_data[G] * scale, m_data[B] * scale, m_data[A] * scale};
		}

		void operator*=(const float rhs) {
			m_data[A] *= rhs;
			m_data[R] *= rhs;
			m_data[G] *= rhs;
			m_data[B] *= rhs;
		}

		Color operator/(const float scale) const {
			return {m_data[R] / scale, m_data[G] / scale, m_data[B] / scale, m_data[A] / scale};
		}

		void operator/=(const float rhs) {
			m_data[A] /= rhs;
			m_data[R] /= rhs;
			m_data[G] /= rhs;
			m_data[B] /= rhs;
		}

		Color operator+(const Color &rhs) const {
			return {m_data[R] + rhs.m_data[R], m_data[G] + rhs.m_data[G],
					m_data[B] + rhs.m_data[B], m_data[A] + rhs.m_data[A]};
		}

		void operator+=(const Color &rhs) {
			m_data[A] += rhs.m_data[A];
			m_data[R] += rhs.m_data[R];
			m_data[G] += rhs.m_data[G];
			m_data[B] += rhs.m_data[B];
		}

		Color operator-(const Color &rhs) const {
			return {m_data[R] - rhs.m_data[R], m_data[G] - rhs.m_data[G],
					m_data[B] - rhs.m_data[B], m_data[A] - rhs.m_data[A]};
		}

		void operator-=(const Color &rhs) {
			m_data[A] -= rhs.m_data[A];
			m_data[R] -= rhs.m_data[R];
			m_data[G] -= rhs.m_data[G];
			m_data[B] -= rhs.m_data[B];
		}

		Color operator*(const Color &rhs) const {
			return {m_data[R] * rhs.m_data[R], m_data[G] * rhs.m_data[G],
					m_data[B] * rhs.m_data[B], m_data[A] * rhs.m_data[A]};
		}

		void operator*=(const Color &rhs) {
			m_data[A] *= rhs.m_data[A];
			m_data[R] *= rhs.m_data[R];
			m_data[G] *= rhs.m_data[G];
			m_data[B] *= rhs.m_data[B];
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

}}

#endif