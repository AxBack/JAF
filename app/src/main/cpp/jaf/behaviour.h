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
	protected:

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

		virtual void normalize() = 0;
    };

};
