//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_COMMANDPOOL_H
#define WUU_COMMANDPOOL_H
#include "LogicalDevice.h"

class CommandPool {
public:

    CommandPool() = default;

    virtual void setPool(LogicalDevice& logicalDevice, const uint32_t&& queueFamilyIndex);
    virtual void destroy(LogicalDevice& logicalDevice);

    [[nodiscard]] auto& getCommandPool() noexcept { return m_commandPool; }
    [[nodiscard]] const auto& getQueueFamilyIndex() const noexcept { return m_queueFamilyIndex; }

protected:

    vk::CommandPool m_commandPool;
    uint32_t m_queueFamilyIndex = 0;

};


#endif //WUU_COMMANDPOOL_H
