//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_MEMORYPOOL_H
#define WUU_MEMORYPOOL_H

#include "CommandPool.h"
#include "Queue.h"

namespace Wuu::Vulkan {

    class MemoryPool {
    public:

        MemoryPool() = default;

        virtual void initialize(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, const uint32_t transferQueueFamilyIndex);

        [[nodiscard]] auto& getCommandPool() noexcept { return m_commandPool; }
        [[nodiscard]] auto& getQueue() noexcept { return m_queue; }

    protected:

        CommandPool m_commandPool;
        Queue m_queue;

    };

}

#endif //WUU_MEMORYPOOL_H
