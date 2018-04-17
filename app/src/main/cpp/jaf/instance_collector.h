#pragma once

#include <vector>

namespace JAF {

    template <typename T>
    class InstanceCollector
    {
    private:

        unsigned int m_index;
        std::vector<T> m_instances;

    public:

        InstanceCollector()
                : m_index(0)
        {}

        void add(T instance)
        {
            if (m_index >= m_instances.size()) {
                m_instances.resize(m_index+1);
            }

            m_instances[m_index++] = instance;
        }

        void begin()
        {
            m_index = 0;
        }

        void end(std::vector<T>& out)
        {
            out.swap(m_instances);
        }
    };
}