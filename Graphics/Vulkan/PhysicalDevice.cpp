//
// Created by Michael Ferents on 11/03/2022.
//

#include "PhysicalDevice.h"

// TODO: This only tries to find it based on its name but instead should find best suited device

void PhysicalDevice::enumeratePhysicalDevices(Instance &instance)
{
    auto physicalDevices = instance.getInstance().enumeratePhysicalDevices();

    m_physicalDevice = physicalDevices[std::distance(physicalDevices.begin(),
                                       std::find_if(physicalDevices.begin(), physicalDevices.end(), [this](const vk::PhysicalDevice& physicalDevice) {
                                           return strstr(physicalDevice.getProperties().deviceName, "GeForce");
                                       }))];

    m_physicalDeviceProperties = m_physicalDevice.getProperties();
}