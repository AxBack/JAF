#pragma once

#include "../pch.h"
#include "../jawe/path.h"
#include "behaviour.h"
#include "../jawe/bank.h"

namespace JAF {

	template <class T>
	class Creator : public BehaviourListener
	{
	protected:

		T* getBehaviour()
		{
			T* item = m_bank.pop();
			item->setListener(this);
			return item;
		}

		void returnBehaviour(T* pItem)
		{
			m_bank.push(pItem);
		}

	private:

		JAWE::Bank<T*> m_bank;

	protected:

		Creator(UINT size)
			: m_bank([](){return new T();}, [](T* p) { delete p; })
		{
			m_bank.resize(size);
		}

	public:

		// TODO: Ill probably have to refactor this at some point. Not really wise to have a strict dependence on Behaviour*.
		virtual void onNotActive(Behaviour* pItem) override
		{
			returnBehaviour(dynamic_cast<T*>(pItem));
		}

		virtual T* create() = 0;

		virtual void step() { }

	};

	template <class T>
	class PathBehaviourCreator : public Creator<T>
	{
	protected:

		typedef Math::Vector3 Vector3;
		typedef Math::Color Color;
		typedef JAWE::Path<Vector3> vec3_path;
		typedef JAWE::Path<float> float_path;
		typedef JAWE::Path<Color> color_path;
		typedef std::shared_ptr<vec3_path> vec3_path_ptr;
		typedef std::shared_ptr<float_path> float_path_ptr;
		typedef std::shared_ptr<color_path> color_path_ptr;

		template <typename K>
		std::shared_ptr<JAWE::Path<K>> createPath(UINT nrPoints, K* p) const
		{
			std::shared_ptr<JAWE::Path<K>> pPath( new JAWE::Path<K>);
			pPath->add(1.0f, nrPoints, p);
			return pPath;
		}

		template <class V, typename K>
		void fill(V* pBehaviour, int nr, BalancedCollection<std::shared_ptr<JAWE::Path<K>>>* pPaths) const
		{
			nr = std::min(nr, (int)pPaths->size());
			int i = 0;
			while(i < nr)
			{
				pBehaviour->add(JAWE::Random::randf(1.0f, 2.0f), pPaths->front().get());
				++i;
			}
		}

	public:

		PathBehaviourCreator(UINT size)
				: Creator<T>(size)
		{
		}
	};
};