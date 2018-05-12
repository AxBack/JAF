#pragma once

#include <vector>
#include <memory>
#include "../pch.h"
#include "quaternion.h"

namespace JAWE {

    template <typename T>
    class Traversable
    {
    protected:

        float m_length { 0 };

    public:

        Traversable(float length)
            : m_length(length)
        {
        }

        virtual ~Traversable() {}

        float getLength() const { return m_length; }
		float setLength(float length) { return m_length = length; }

        virtual T traverse(float dt) = 0;
    };

    template <typename T>
    class Single : public Traversable<T>
    {
    private:

        T m_value;

    public:

        Single(float length, T value)
                : Traversable<T>(length)
                , m_value(value)
        {
        }

        virtual T traverse(float dt) override { return m_value; }
    };

    template <typename T>
    class Linear : public Traversable<T>
    {
    private:

        T m_start;
        T m_end;

    public:

        Linear(float length, T start, T end)
                : Traversable<T>(length)
                , m_start(start)
                , m_end(end)
        {
        }

        virtual T traverse(float dt) override
        {
            if(dt <= 0.0f)
                return m_start;
            if(dt >= 1.0f)
                return m_end;

            return (m_start * (1.0f - dt)) + (m_end * dt);
        }
    };

	template <typename T>
	class Quadratic : public Traversable<T>
	{
	private:

		T m_start;
		T m_middle;
		T m_end;

	public:

		Quadratic(float length, T start, T middle, T end)
				: Traversable<T>(length)
				, m_start(start)
			    , m_middle(middle)
				, m_end(end)
		{
		}

		virtual T traverse(float dt) override
		{
			if(dt <= 0.0f)
				return m_start;
			if(dt >= 1.0f)
				return m_end;

			float inv = 1.0f - dt;
			return (((m_start * inv) + (m_middle * dt)) * inv) + (((m_middle * inv) + (m_end * dt)) * dt);
		}
	};

	template <typename T>
	class Cubic : public Traversable<T>
	{
	private:

		T m_p1;
		T m_c1;
		T m_c2;
		T m_p2;

	public:

		Cubic(float length, T p1, T c1, T c2, T p2)
				: Traversable<T>(length)
				, m_p1(p1)
				, m_c1(c1)
				, m_c2(c2)
				, m_p2(p2)
		{
		}

		virtual T traverse(float dt) override
		{
			if(dt <= 0.0f)
				return m_p1;
			if(dt >= 1.0f)
				return m_p2;

			float inv = 1.0f - dt;
			T d1 = (m_p1 * inv) + (m_c1 * dt);
			T d2 = (m_c1 * inv) + (m_c2 * dt);
			T d3 = (m_c2 * inv) + (m_p2 * dt);
			return ((d1 * inv) + (d2 * dt)) * inv + ((d2 * inv) + (d3 * dt)) * dt;
		}
	};


    template <typename T>
    class Bezier : public Traversable<T>
    {
    private:

        std::vector<T> m_points;
		std::vector<T> m_backup;

    public:

        Bezier(float length, UINT nrPoints, const T* pPoints)
                :Traversable<T>(length)
        {
            m_points = std::vector<T>(pPoints, pPoints+nrPoints);
			m_backup = std::vector<T>(m_points);
        }

        virtual T traverse(float dt) override
        {
            if(dt <= 0.0f)
                return m_points[0];
            if(dt >= 1.0f)
                return m_points[m_points.size()-1];

			memcpy(&m_backup[0], &m_points[0], sizeof(T) * m_points.size());
            UINT i = static_cast<UINT>(m_points.size())-1;
            while(i > 0 )
            {
                for(UINT j=0; j<i; ++j)
					m_backup[j] += (m_backup[j+1] - m_backup[j]) * dt;

                --i;
            }

            return m_backup[0];
        }
    };

    template <typename T>
    class Path
    {
    private:

        typedef std::shared_ptr<Traversable<T>> traversable_ptr;

        std::vector<traversable_ptr> m_traversables;

        float m_totalLength;

    public:

        Path()
            : m_totalLength(0)
        {
        }

        void clear()
        {
            m_traversables.clear();
            m_totalLength = 0;
        }

        void add(float length, UINT nrControlPoints, const T* pControlPoints)
        {
            traversable_ptr p;
            switch (nrControlPoints)
            {
                case 0:
                    return;
                case 1:
                    p = traversable_ptr(new Single<T>(length, pControlPoints[0]));
                    break;
                case 2:
                    p = traversable_ptr(new Linear<T>(length, pControlPoints[0], pControlPoints[1]));
                    break;
				case 3:
					p = traversable_ptr(new Quadratic<T>(length, pControlPoints[0], pControlPoints[1], pControlPoints[2]));
					break;
				case 4:
					p = traversable_ptr(new Cubic<T>(length, pControlPoints[0], pControlPoints[1], pControlPoints[2], pControlPoints[3]));
					break;
                default:
                    p = traversable_ptr(new Bezier<T>(length, nrControlPoints, pControlPoints));
                    break;
            }

            m_totalLength += length;
            m_traversables.push_back(p);
        }

        void normalize()
        {
            for(auto& it : m_traversables)
                it->setLength(it->getLength() / m_totalLength);

            m_totalLength = 1.0f;
        }

        T traverse(float time)
        {
            if(m_traversables.size() <= 0)
                return T();

            for(auto& it : m_traversables)
            {
                if(it->getLength() >= time)
                {
                    float dt = time / it->getLength();
                    return it->traverse(dt);
                }
                else
                    time -= it->getLength();
            }

            return (*m_traversables.rbegin())->traverse(1.0f);
        }

        float getLength() const { return m_totalLength; }
    };

}