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

    class BehaviourInfluenced
    {
    public:

        virtual void setPosition(const Math::Vector3& position) = 0;
        virtual void setRadius(const float size) = 0;
        virtual void setColor(const Math::Color& color) = 0;
    };

	class Behaviour;

	class BehaviourListener
	{
	public:

		virtual void onNotActive(Behaviour* pBehaviour) = 0;
	};

	class Behaviour
	{
	protected:

		BehaviourListener* m_pListener { nullptr };

		int m_nrActive { 0 };
		float m_timeLimit { 0 };

	public:

		void setListener(BehaviourListener* pListener) { m_pListener = pListener; }

		virtual void init(float time)
		{
			m_timeLimit = time;
		}

		bool active() const { return m_nrActive > 0; }

		virtual void fire(BehaviourInfluenced* pItem) {++m_nrActive; }
		virtual void end(BehaviourInfluenced* pItem)
		{
			--m_nrActive;
			if(m_pListener && m_nrActive <= 0)
				m_pListener->onNotActive(this);
		}
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
