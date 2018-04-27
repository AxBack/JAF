#pragma once

#include <random>
#include "../jawe/vector3.h"
#include "../jawe/color.h"
#include "../jawe/path.h"
#include "../jawe/random.h"

namespace JAF {

    typedef std::shared_ptr<JAWE::Path<Math::Vector3>> vec3_path_ptr;
    typedef std::shared_ptr<JAWE::Path<float>> float_path_ptr;
    typedef std::shared_ptr<JAWE::Path<Math::Color>> color_path_ptr;

	class Particle;

    class BehaviourInfluenced
    {
    public:

        virtual void setPosition(const Math::Vector3& position) = 0;
        virtual void setRadius(const float size) = 0;
        virtual void setColor(const Math::Color& color) = 0;
    };

	class Behaviour
	{
	protected:
		float m_timeLimit { 0 };

	public:

		virtual void init(float time)
		{
			m_timeLimit = time;
		}

		virtual void fire(Particle* pParticle) = 0;

		virtual bool update(BehaviourInfluenced* pItem, float dt) = 0;

	};

    class PathBehaviour : public Behaviour
    {
    private:

        std::vector<std::pair<float, vec3_path_ptr>> m_positions;
        std::vector<std::pair<float, float_path_ptr>> m_sizes;
        std::vector<std::pair<float, color_path_ptr>> m_colors;

        template <typename T>
        T update(T v, const std::vector<std::pair<float, std::shared_ptr<JAWE::Path<T>>>>& paths, float time)
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

		void normalize()
		{
			normalize(m_positions);
			normalize(m_sizes);
			normalize(m_colors);
		}

        void add(float weight, vec3_path_ptr pPosition)
        {
            m_positions.push_back(std::make_pair(weight, pPosition));
        }

        void add(float weight, float_path_ptr pSize)
        {
            m_sizes.push_back(std::make_pair(weight, pSize));
        }
        void add(float weight, color_path_ptr pColor)
        {
            m_colors.push_back(std::make_pair(weight, pColor));
        }

		virtual void fire(Particle* pParticle) override {}
        virtual bool update(BehaviourInfluenced* pItem, float time) override;
    };

};
