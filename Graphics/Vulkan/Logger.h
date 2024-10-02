//
// Created by Michael Ferents on 01/08/2023.
//

#ifndef WUU_LOGGER_H
#define WUU_LOGGER_H
#include <vector>
#include <chrono>
#include <ctime>

template<typename DataType>
class Logger {
public:

    using DataPoint = std::pair<std::time_t, DataType>;

    Logger() = default;

    void log(DataType logMessage) noexcept
    {
        auto start = std::time(nullptr);

        m_log.push_back(std::pair(start, logMessage));
    }

    void print() const noexcept
    {
        for(const auto& message : m_log)
        {
            std::cout << std::asctime(std::localtime(&message.first)) << message.second.to_string() << std::endl;
        }
    }

private:

    std::vector<DataPoint> m_log;

};


#endif //WUU_LOGGER_H
