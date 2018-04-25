#pragma once

#include <random>
#include "../jawe/vector3.h"
#include "../jawe/color.h"
#include "../jawe/path.h"
#include "../jawe/random.h"

namespace JAF {

    typedef JAWE::Path<Math::Vector3> vec3_path;
    typedef JAWE::Path<float> float_path;
    typedef JAWE::Path<Math::Color> color_path;
    typedef std::vector<std::pair<int, float>> int_float_vec;

    class BehaviourInfluenced
    {
    public:

        virtual void setPosition(const Math::Vector3& position) = 0;
        virtual void setRadius(const float size) = 0;
        virtual void setColor(const Math::Color& color) = 0;
    };

    class Behaviour
    {
    private:

        float m_timeLimit { 0 };

        std::vector<std::pair<float, const vec3_path*>> m_positions;
        std::vector<std::pair<float, const float_path*>> m_sizes;
        std::vector<std::pair<float, const color_path*>> m_colors;

        template <typename T>
        T update(T v, const std::vector<std::pair<float, const JAWE::Path<T>*>>& paths, float time) const
        {
            for(auto& it : paths)
                v += it.second->traverse(time) * it.first;
            return v;
        }

		template <typename T>
		void normalize(std::vector<std::pair<float, T>>& vec)
		{
			float total = 0;
			for(auto& it : vec)
				total += it.first;

			for(auto& it : vec)
				it.first = it.first / total;
		}

    public:

        void init(float time)
        {
            m_timeLimit = time;
        }

		void normalize()
		{
			normalize(m_positions);
			normalize(m_sizes);
			normalize(m_colors);
		}

        void addPosition(float weight, const vec3_path* path)
        {
            m_positions.push_back(std::make_pair(weight, path));
        }

        void addSize(float weight, const float_path* path)
        {
            m_sizes.push_back(std::make_pair(weight, path));
        }
        void addColor(float weight, const color_path* path)
        {
            m_colors.push_back(std::make_pair(weight, path));
        }

        bool update(BehaviourInfluenced* pItem, float time) const;
    };

};
