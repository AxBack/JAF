#pragma once

#include <random>
#include "../jawe/vector3.h"
#include "../jawe/color.h"
#include "../jawe/path.h"

namespace JAF {

    typedef JAWE::Path<Math::Vector3> vec3_path;
    typedef JAWE::Path<float> float_path;
    typedef JAWE::Path<Math::Color> color_path;
    typedef std::vector<std::pair<int, float>> int_float_vec;

    class BehaviourInfluenced
    {
    protected:

        int_float_vec 	m_positionWeights;
        int_float_vec 	m_sizeWeights;
        int_float_vec 	m_color_weights;

    public:

        void setPositionWeights(int_float_vec&& weights) { m_positionWeights = weights;}
        void setSizeWeights(int_float_vec&& weights) { m_sizeWeights = weights;}
        void setColorWeights(int_float_vec&& weights) { m_color_weights = weights;}

        const int_float_vec* getPositionWeights() { return &m_positionWeights; }
        const int_float_vec* getSizeWeights() { return &m_sizeWeights; }
        const int_float_vec* getColorWeights() { return &m_color_weights; }

        virtual void setPosition(const Math::Vector3& position) = 0;
        virtual void setSize(const float size) = 0;
        virtual void setColor(const Math::Color& color) = 0;
    };

    class Behaviour
    {
    private:

        float m_timeLimit { 0 };

        float m_totalPositionWeights { 0 };
        std::vector<std::pair<float, const vec3_path*>> m_positions;

        float m_totalSizeWeights { 0 };
        std::vector<std::pair<float, const float_path*>> m_sizes;

        float m_totalColorWeights { 0 };
        std::vector<std::pair<float, const color_path*>> m_colors;

        template <typename T>
		int_float_vec createDistribution(std::mt19937& generator, const std::vector<std::pair<float, T>>& paths) const
        {
			int_float_vec out;
            std::uniform_real_distribution<float> dist(0.0f,1.0f);
            float total = 0;
            int i = 0;
            for(auto& it : paths)
            {
                float v = it.first * dist(generator);
                out.push_back(std::make_pair(i++, v));
                total += v;
            }

            for(auto& it : out)
                it.second /= total;

			return std::move(out);
        }

        template <typename T>
        T update(T v, const int_float_vec* pWeights, const std::vector<std::pair<float, const JAWE::Path<T>*>>& paths, float time) const
        {
            for(auto& it : *pWeights)
                v += paths[it.first].second->traverse(time) * it.second;
            return v;
        }

    public:

        void init(float time)
        {
            m_timeLimit = time;
        }

        void addPosition(float weight, const vec3_path* path)
        {
            m_totalPositionWeights += weight;
            m_positions.push_back(std::make_pair(weight, path));
        }

        void addSize(float weight, const float_path* path)
        {
            m_totalSizeWeights += weight;
            m_sizes.push_back(std::make_pair(weight, path));
        }
        void addColor(float weight, const color_path* path)
        {
            m_totalColorWeights += weight;
            m_colors.push_back(std::make_pair(weight, path));
        }

        void fire(std::mt19937& generator, BehaviourInfluenced* pItem) const;
        bool update(BehaviourInfluenced* pItem, float time) const;
    };

};
