//
// Created by Michael Ferents on 11/03/2022.
//

#include "LogicalDevice.h"

using namespace Wuu::Vulkan;

void LogicalDevice::initializeLogicalDevice(Surface &surface, PhysicalDevice &physicalDevice)
{
    auto queueFamilyProperties = physicalDevice.getPhysicalDevice().getQueueFamilyProperties();

    size_t graphicsQueueFamilyIndex = std::distance(queueFamilyProperties.begin(),
                                                    std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(),
                                                                 [](vk::QueueFamilyProperties const& qfp) {
                                                        return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
                                                    }));

    size_t presentQueueFamilyIndex = 0u;
    for(auto i = 0ul; i < queueFamilyProperties.size(); i++)
    {
        if(physicalDevice.getPhysicalDevice().getSurfaceSupportKHR(static_cast<uint32_t>(i), surface.getSurface()))
        {
            presentQueueFamilyIndex = i;
        }
    }

    size_t transferQueueFamilyIndex = std::distance(queueFamilyProperties.begin(),
                                                    std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(),
                                                                 [](vk::QueueFamilyProperties const& qfp) {
                                                        return qfp.queueFlags & vk::QueueFlagBits::eTransfer;
                                                    }));

    std::set<uint32_t> uniqueQueueFamilyIndices = { static_cast<uint32_t>(graphicsQueueFamilyIndex),
                                                    static_cast<uint32_t>(presentQueueFamilyIndex),
                                                    static_cast<uint32_t>(transferQueueFamilyIndex)};

    std::vector<uint32_t> FamilyIndices = { uniqueQueueFamilyIndices.begin(),
                                            uniqueQueueFamilyIndices.end() };
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos {};

    float queuePriority = 0.0f;
    for(auto& queueFamilyIndex : uniqueQueueFamilyIndices)
    {
        queueCreateInfos.emplace_back(vk::DeviceQueueCreateFlags(),
                                      static_cast<uint32_t>(queueFamilyIndex), 1, &queuePriority);
    }

    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            "VK_KHR_portability_subset"
            };

    vk::PhysicalDeviceFeatures deviceFeatures {};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    vk::DeviceCreateInfo deviceCreateInfo {};
    deviceCreateInfo.flags = vk::DeviceCreateFlags();
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.enabledLayerCount = 0u;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    m_logicalDevice = physicalDevice.getPhysicalDevice().createDevice(deviceCreateInfo);

    m_graphicsQueueFamilyIndex = graphicsQueueFamilyIndex;
    m_presentQueueFamilyIndex = presentQueueFamilyIndex;
    m_transferQueueFamilyIndex = transferQueueFamilyIndex;
}

void LogicalDevice::destroy()
{
    m_logicalDevice.destroy();
}