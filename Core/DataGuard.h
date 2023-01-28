//
// Created by Michael Ferents on 26/03/2022.
//

#ifndef WUU_DATAGUARD_H
#define WUU_DATAGUARD_H
#include <vector>
#include <mutex>

namespace Wuu
{

    struct empty_stack : std::exception
    {
        const char* what() const throw();
    };

    template<typename T>
    class DataGuard {
    public:

        DataGuard() = default;

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_values.push_back(std::move(new_value));
        }

        void pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if(m_values.empty()) throw empty_stack();
            value = std::move(m_values.front());
            m_values.pop_back();
        }

        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if(m_values.empty()) throw empty_stack();
            std::shared_ptr<T> const res {
                    std::make_shared<T>(std::move(m_values.front()))
            };
            m_values.pop_back();
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_values.empty();
        }

    private:

        std::vector<T> m_values;
        mutable std::mutex m_mutex;

    };
}

#endif //WUU_DATAGUARD_H
