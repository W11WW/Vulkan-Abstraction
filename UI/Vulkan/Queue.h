//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_QUEUE_H
#define WUU_QUEUE_H
#include "LogicalDevice.h"

namespace Wuu::Vulkan {

    class Queue {
    public:

        Queue() = default;

        virtual void setQueue(LogicalDevice& logicalDevice, const uint32_t queueFamilyIndex);

        [[nodiscard]] auto& getQueue() noexcept { return m_queue; }

    protected:

        vk::Queue m_queue;

    };

}


#endif //WUU_QUEUE_H
