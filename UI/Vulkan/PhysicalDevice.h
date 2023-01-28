//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_PHYSICALDEVICE_H
#define WUU_PHYSICALDEVICE_H
#include "Instance.h"
#include <string>
#include <string_view>

// TODO: organize physical and logical device better

namespace Wuu::Vulkan {

    class PhysicalDevice {
    public:

        explicit PhysicalDevice(std::string_view customDevice = "DeForce") : m_physicalDeviceName(customDevice) {}

        virtual void enumeratePhysicalDevices(Instance& instance);

        [[nodiscard]] auto& getPhysicalDevice() noexcept { return m_physicalDevice; }
        [[nodiscard]] const auto& getPhysicalDeviceName() const noexcept { return m_physicalDeviceName; }

    protected:

        std::string m_physicalDeviceName;
        vk::PhysicalDevice m_physicalDevice;

    };

}


#endif //WUU_PHYSICALDEVICE_H
