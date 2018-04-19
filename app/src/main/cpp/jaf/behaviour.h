#pragma once

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

        int_float_vec m_positionWeights;
        int_float_vec m_sizeWeights;
        int_float_vec m_color_weights;

    public:

        void setPositionWeights(int_float_vec&& weights) { m_positionWeights = std::move(weights);}
        void setSizeWeights(int_float_vec&& weights) { m_sizeWeights = std::move(weights);}
        void setColornWeights(int_float_vec&& weights) { m_color_weights = std::move(weights);}

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
        float m_timeLimit;

        float m_totalPositionWeights;
        std::vector<std::pair<float, const vec3_path*>> m_positions;

        float m_totalSizeWeights;
        std::vector<std::pair<float, const float_path*>> m_sizes;

        float m_totalColorWeights;
        std::vector<std::pair<float, const color_path*>> m_colors;

        /*
        const vec3_path* m_pPosition;
        const float_path* m_pSize;
        const color_path* m_pColor;
         */

    public:

        Behaviour()
                : m_timeLimit(0)
                , m_totalPositionWeights(0)
                , m_totalSizeWeights(0)
                , m_totalColorWeights(0)
        {}

        virtual void init(float time)
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

        void fire(BehaviourInfluenced* pItem) const;

        bool update(BehaviourInfluenced* pItem, float time) const;
    };
}
