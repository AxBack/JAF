#pragma once

#include "../pch.h"
#include "../jawe/path.h"
#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	class Creator
	{
	protected:

		typedef std::shared_ptr<Behaviour> behaviour_ptr;
		typedef JAWE::Bank<Behaviour> behaviour_bank;
		typedef Math::Vector3 Vector3;
		typedef Math::Color Color;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef JAWE::Path<float> float_path;
		typedef JAWE::Path<Color> color_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;
		typedef std::shared_ptr<float_path> float_path_ptr;
		typedef std::shared_ptr<color_path> color_path_ptr;

	private:

		behaviour_bank m_behaviourBank;


	protected:

		Creator()
			: m_behaviourBank([](){return new Behaviour();})
		{
			for(UINT i=0; i<10; ++i)
				m_behaviourBank.push(m_behaviourBank.pop());
		}

		behaviour_ptr getBehaviour()
		{
			behaviour_ptr p = m_behaviourBank.pop();
			m_behaviourBank.push(p);
			return p;
		}

		template <typename T> std::shared_ptr<JAWE::Path<T>> createPath(float time, UINT nrPoints, T* p)
		{
			std::shared_ptr<JAWE::Path<T>> pPath( new JAWE::Path<T>);
			pPath->add(time, nrPoints, p);
			return pPath;
		}

		template <typename T> void fill(Behaviour* pBehaviour, int nr, BalancedCollection<std::shared_ptr<JAWE::Path<T>>>* pPaths)
		{
			nr = std::min(nr, (int)pPaths->size());
			int i = 0;
			while(i < nr)
			{
				pBehaviour->add(JAWE::Random::rand(1.0f, 2.0f), pPaths->front().get());
				++i;
			}
		}

	public:

		virtual const Behaviour* create() = 0;

	};
};