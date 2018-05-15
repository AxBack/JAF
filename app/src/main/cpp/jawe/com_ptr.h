#pragma once

#include <functional>

namespace JAWE {

    template <typename T> class ComPtr
    {
    private:

        T m_pItem {nullptr};
        std::function<void(T)> m_destructor;

    public:

        ComPtr(T p, std::function<void(T)> destructor)
        {
            m_pItem = p;
            m_destructor = destructor;
        }

        ComPtr(std::function<void(T)> destructor)
        {
            m_destructor = destructor;
        }

        void set(T p) { m_pItem = p; }

        ~ComPtr()
        {
            if(m_pItem)
            {
                m_destructor(m_pItem);
            }
        }

        T get() { return m_pItem; }

    };

}