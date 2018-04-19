#pragma once

#include <queue>


namespace JAWE {

    template <typename T>
    class Bank
    {
    private:

        std::queue<std::shared_ptr<T>> m_queue;

    public:

        std::shared_ptr<T> pop()
        {
            if(m_queue.size() == 0)
                return std::shared_ptr<T>(new T);

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