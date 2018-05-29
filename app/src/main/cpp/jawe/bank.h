#pragma once

#include <queue>
#include "../pch.h"


namespace JAWE {

    template <typename T>
    class Bank
    {
    private:

        std::queue<T> m_queue;

        std::function<T()> m_allocator;
		std::function<void(T)> m_deleter;

		T createNew() { return m_allocator(); }

    public:

        Bank(std::function<T()>&& allocator, std::function<void(T)>&& deleter = [](T){})
                : m_allocator(allocator)
				, m_deleter(deleter)
        {
        }

		virtual ~Bank()
		{
			while(m_queue.size() > 0)
			{
				T p = m_queue.front();
				m_queue.pop();
				m_deleter(p);
			}
		}

		void resize(UINT size)
		{
			while(size < m_queue.size())
				m_queue.pop();

			while (size > m_queue.size())
				m_queue.push(createNew());
		}

        T pop()
        {
            if(m_queue.size() == 0)
                return createNew();

            auto t = m_queue.front();
            m_queue.pop();
            return t;
        }

        void push(T p)
        {
            m_queue.push(p);
        }
    };
}