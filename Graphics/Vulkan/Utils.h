//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_UTILS_H
#define WUU_UTILS_H
#include "PhysicalDevice.h"

#include <vector>
#include <fstream>

typedef struct InstanceCreateInfo {

    bool m_enableValidationLayers = true;

    std::string m_applicationName = "Vulkan-Abstraction";
    uint16_t m_applicationVersion = 1;

    std::string m_engineName = "WuranEngine";
    uint16_t m_engineVersion = 1;

} InstanceCreateInfo;



static std::vector<char> readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if(!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

static uint32_t findMemoryType(PhysicalDevice& physicalDevice, const uint32_t typeFilter, const vk::Flags<vk::MemoryPropertyFlagBits> properties)
{
    vk::PhysicalDeviceMemoryProperties memoryProperties = physicalDevice.getPhysicalDevice().getMemoryProperties();

    for(uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Failed to find a suitable memory type");
}

#endif //WUU_UTILS_H
