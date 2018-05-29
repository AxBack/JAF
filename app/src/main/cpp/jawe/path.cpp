#include "path.h"

#include "utils.h"

#if defined(__ARM_NEON)

namespace JAWE {

    static float32x4_t lerp(float32x4_t lhs, float32x4_t rhs, float dt)
    {
        return vaddq_f32(vmulq_n_f32(lhs, 1.0f - dt), vmulq_n_f32(rhs, dt));
    }

    /************ Linear *****************/

    template <>
    MATH::Vector3 Linear<MATH::Vector3>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_start;
        if(dt >= 1.0f)
            return m_end;

        if(Utils::SIMD::ready)
        {
            float v[4];
            vst1q_f32(v, lerp(vld1q_f32(m_start.data()), vld1q_f32(m_end.data()), dt));
            return {v[0], v[1], v[2]};
        }

        return (m_start * (1.0f - dt)) + (m_end * dt);
    }

    template <>
    MATH::Color Linear<MATH::Color>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_start;
        if(dt >= 1.0f)
            return m_end;

        if(Utils::SIMD::ready)
        {
            float v[4];
            vst1q_f32(v, lerp(vld1q_f32(m_start.data()), vld1q_f32(m_end.data()), dt));
            return {v[0], v[1], v[2], v[3]};
        }

        return (m_start * (1.0f - dt)) + (m_end * dt);
    }

    /************ Quadratic *****************/

    template <>
    MATH::Vector3 Quadratic<MATH::Vector3>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_start;
        if(dt >= 1.0f)
            return m_end;

        if(Utils::SIMD::ready)
        {
            float32x4_t s =vld1q_f32(m_start.data());
            float32x4_t m =vld1q_f32(m_middle.data());
            float32x4_t e =vld1q_f32(m_end.data());

            float v[4];
            vst1q_f32(v, lerp( lerp(s, m, dt), lerp(m, e, dt), dt));
            return {v[0], v[1], v[2]};
        }

        float inv = 1.0f - dt;
        return (((m_start * inv) + (m_middle * dt)) * inv) + (((m_middle * inv) + (m_end * dt)) * dt);
    }

    template <>
    MATH::Color Quadratic<MATH::Color>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_start;
        if(dt >= 1.0f)
            return m_end;

        if(Utils::SIMD::ready)
        {
            float32x4_t s =vld1q_f32(m_start.data());
            float32x4_t m =vld1q_f32(m_middle.data());
            float32x4_t e =vld1q_f32(m_end.data());

            float v[4];
            vst1q_f32(v, lerp( lerp(s, m, dt), lerp(m, e, dt), dt));
            return {v[0], v[1], v[2], v[3]};
        }

        float inv = 1.0f - dt;
        return (((m_start * inv) + (m_middle * dt)) * inv) + (((m_middle * inv) + (m_end * dt)) * dt);
    }

    /************ Cubic *****************/

    template <>
    MATH::Vector3 Cubic<MATH::Vector3>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_p1;
        if(dt >= 1.0f)
            return m_p2;

        if(Utils::SIMD::ready)
        {
            float32x4_t p1 = vld1q_f32(m_p1.data());
            float32x4_t c1 = vld1q_f32(m_c1.data());
            float32x4_t c2 = vld1q_f32(m_c2.data());
            float32x4_t p2 = vld1q_f32(m_p2.data());

            float32x4_t s = lerp(p1, c1, dt);
            float32x4_t m = lerp(c1, c2, dt);
            float32x4_t e = lerp(c2, p2, dt);

            float v[4];
            vst1q_f32(v, lerp( lerp(s, m, dt), lerp(m, e, dt), dt));
            return {v[0], v[1], v[2]};
        }

        float inv = 1.0f - dt;
        MATH::Vector3 d1 = (m_p1 * inv) + (m_c1 * dt);
        MATH::Vector3 d2 = (m_c1 * inv) + (m_c2 * dt);
        MATH::Vector3 d3 = (m_c2 * inv) + (m_p2 * dt);
        return ((d1 * inv) + (d2 * dt)) * inv + ((d2 * inv) + (d3 * dt)) * dt;
    }

    template <>
    MATH::Color Cubic<MATH::Color>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_p1;
        if(dt >= 1.0f)
            return m_p2;

        if(Utils::SIMD::ready)
        {
            float32x4_t p1 = vld1q_f32(m_p1.data());
            float32x4_t c1 = vld1q_f32(m_c1.data());
            float32x4_t c2 = vld1q_f32(m_c2.data());
            float32x4_t p2 = vld1q_f32(m_p2.data());

            float32x4_t s = lerp(p1, c1, dt);
            float32x4_t m = lerp(c1, c2, dt);
            float32x4_t e = lerp(c2, p2, dt);

            float v[4];
            vst1q_f32(v, lerp( lerp(s, m, dt), lerp(m, e, dt), dt));
            return {v[0], v[1], v[2], v[3]};
        }

        float inv = 1.0f - dt;
        MATH::Color d1 = (m_p1 * inv) + (m_c1 * dt);
        MATH::Color d2 = (m_c1 * inv) + (m_c2 * dt);
        MATH::Color d3 = (m_c2 * inv) + (m_p2 * dt);
        return ((d1 * inv) + (d2 * dt)) * inv + ((d2 * inv) + (d3 * dt)) * dt;
    }

    /************ Bezier *****************/

    float32x4_t bezier(UINT nr, float32x4_t* pPoints, float dt)
    {
        UINT i = static_cast<UINT>(nr)-1;
        while(i > 0 )
        {
            for(UINT j=0; j<i; ++j)
                pPoints[j] = vaddq_f32(pPoints[j], vmulq_n_f32(vsubq_f32(pPoints[j+1], pPoints[j]), dt));
            --i;
        }
        return pPoints[0];
    }

    template <>
    MATH::Vector3 Bezier<MATH::Vector3>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_points[0];
        if(dt >= 1.0f)
            return m_points[m_points.size()-1];

        if(Utils::SIMD::ready)
        {
            float32x4_t* pPoints = new float32x4_t[m_points.size()];
            for(UINT i=0; i<m_points.size(); ++i)
                pPoints[i] = vld1q_f32(m_points[i].data());

            float v[4];
            vst1q_f32(v, bezier(static_cast<UINT>(m_points.size()), pPoints, dt));

            _safe_delete_array(pPoints);
            return {v[0], v[1], v[2]};
        }

        UINT i = static_cast<UINT>(m_points.size())-1;
        while(i > 0 )
        {
            for(UINT j=0; j<i; ++j)
                m_backup[j] += (m_backup[j+1] - m_backup[j]) * dt;

            --i;
        }
        return m_backup[0];
    }

    template <>
    MATH::Color Bezier<MATH::Color>::traverse(float dt)
    {
        if(dt <= 0.0f)
            return m_points[0];
        if(dt >= 1.0f)
            return m_points[m_points.size()-1];

        if(Utils::SIMD::ready)
        {
            float32x4_t* pPoints = new float32x4_t[m_points.size()];
            for(UINT i=0; i<m_points.size(); ++i)
                pPoints[i] = vld1q_f32(m_points[i].data());

            float v[4];
            vst1q_f32(v, bezier(static_cast<UINT>(m_points.size()), pPoints, dt));
            _safe_delete_array(pPoints);
            return {v[0], v[1], v[2], v[3]};
        }

        UINT i = static_cast<UINT>(m_points.size())-1;
        while(i > 0 )
        {
            for(UINT j=0; j<i; ++j)
                m_backup[j] += (m_backup[j+1] - m_backup[j]) * dt;

            --i;
        }
        return m_backup[0];
    }
}

#endif
