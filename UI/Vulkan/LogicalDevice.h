//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_LOGICALDEVICE_H
#define WUU_LOGICALDEVICE_H
#include "Surface.h"
#include "PhysicalDevice.h"
#include <set>
// TODO: set to only use 3 queues but everything should be virtual so you can make it custom

namespace Wuu::Vulkan {

    class LogicalDevice {
    public:

        LogicalDevice() = default;

        virtual void initializeLogicalDevice(Surface& surface, PhysicalDevice& physicalDevice);
        virtual void destroy();

        auto& getLogicalDevice() noexcept { return m_logicalDevice; }

        [[nodiscard]] const auto& getGraphicsQueueIndex() const noexcept { return m_graphicsQueueFamilyIndex; }
        [[nodiscard]] const auto& getPresentQueueIndex() const noexcept { return m_presentQueueFamilyIndex; }
        [[nodiscard]] const auto& getTransferQueueIndex() const noexcept { return m_transferQueueFamilyIndex; }

    protected:

        vk::Device m_logicalDevice;

        uint32_t m_graphicsQueueFamilyIndex;
        uint32_t m_presentQueueFamilyIndex;
        uint32_t m_transferQueueFamilyIndex;

    };

}


#endif //WUU_LOGICALDEVICE_H
