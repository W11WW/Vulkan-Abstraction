//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_PHYSICALDEVICE_H
#define WUU_PHYSICALDEVICE_H
#include "Instance.h"
#include <string>
#include <string_view>

// TODO: organize physical and logical device better

class PhysicalDevice {
public:

    explicit PhysicalDevice(std::string_view customDevice = "DeForce") {}

    virtual void enumeratePhysicalDevices(Instance& instance);

    [[nodiscard]] auto& getPhysicalDevice() noexcept { return m_physicalDevice; }
    [[nodiscard]] const auto& getPhysicalDeviceProperties() const noexcept { return m_physicalDeviceProperties; }

protected:

    vk::PhysicalDevice m_physicalDevice;
    vk::PhysicalDeviceProperties m_physicalDeviceProperties;

};


#endif //WUU_PHYSICALDEVICE_H
