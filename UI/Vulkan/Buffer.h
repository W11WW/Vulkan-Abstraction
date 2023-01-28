//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_BUFFER_H
#define WUU_BUFFER_H

#include "LogicalDevice.h"
#include <vulkan/vulkan.hpp>

namespace Wuu::Vulkan {

    class Buffer {
    public:

        Buffer() = default;

        virtual void destroy(LogicalDevice& logicalDevice);

        [[nodiscard]] auto& getBuffer() noexcept { return m_buffer; }
        [[nodiscard]] auto& getDeviceMemory() noexcept { return m_deviceMemory; }

    protected:

        vk::Buffer m_buffer;
        vk::DeviceMemory m_deviceMemory;

    };

}


#endif //WUU_BUFFER_H
