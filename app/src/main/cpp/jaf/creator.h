#pragma once

#include "../pch.h"
#include "../jawe/path.h"
#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	template <class T>
	class Creator
	{
	protected:

		std::shared_ptr<T> get()
		{
			std::shared_ptr<T> p = m_bank.pop();
			m_bank.push(p);
			return p;
		}

	private:

		JAWE::Bank<T> m_bank;

	protected:

		Creator(UINT size)
			: m_bank([](){return new T();})
		{
			m_bank.resize(size);
		}

	public:

		virtual std::shared_ptr<T> create() = 0;

	};

	class PathBehaviourCreator : public Creator<PathBehaviour>
	{
	protected:

		typedef std::shared_ptr<PathBehaviour> behaviour_ptr;
		typedef Math::Vector3 Vector3;
		typedef Math::Color Color;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef JAWE::Path<float> float_path;
		typedef JAWE::Path<Color> color_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;
		typedef std::shared_ptr<float_path> float_path_ptr;
		typedef std::shared_ptr<color_path> color_path_ptr;

		template <typename T> std::shared_ptr<JAWE::Path<T>> createPath(float time, UINT nrPoints, T* p)
		{
			std::shared_ptr<JAWE::Path<T>> pPath( new JAWE::Path<T>);
			pPath->add(time, nrPoints, p);
			return pPath;
		}

		template <typename T> void fill(PathBehaviour* pBehaviour, int nr, BalancedCollection<std::shared_ptr<JAWE::Path<T>>>* pPaths)
		{
			nr = std::min(nr, (int)pPaths->size());
			int i = 0;
			while(i < nr)
			{
				pBehaviour->add(JAWE::Random::randf(1.0f, 2.0f), pPaths->front());
				++i;
			}
		}

	public:

		PathBehaviourCreator(UINT size)
				: Creator(size)
		{
		}

	};
};