#pragma once

#include <queue>


namespace JAWE {

    template <typename T>
    class Bank
    {
    private:

        std::queue<std::shared_ptr<T>> m_queue;

        std::function<T*()> newInstance;

		std::shared_ptr<T> createNew() { return std::shared_ptr<T>(newInstance()); }

    public:

        Bank(std::function<T*()>&& newInstance)
                : newInstance(newInstance)
        {
        }

		void resize(UINT size)
		{
			while(size < m_queue.size())
				m_queue.pop();

			while (size > m_queue.size())
				m_queue.push(createNew());
		}

        std::shared_ptr<T> pop()
        {
            if(m_queue.size() == 0)
                return createNew();

            auto t = m_queue.front();
            m_queue.pop();
            return t;
        }

        void push(std::shared_ptr<T> p)
        {
            m_queue.push(p);
        }
    };
}