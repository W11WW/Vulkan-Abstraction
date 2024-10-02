//
// Created by Michael Ferents on 12/03/2022.
//

#include "CommandPool.h"

void CommandPool::setPool(LogicalDevice &logicalDevice, const uint32_t &&queueFamilyIndex)
{
    m_queueFamilyIndex = queueFamilyIndex;
    vk::CommandPoolCreateInfo createInfo = {};
    createInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    createInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamilyIndex);
    m_commandPool = logicalDevice.getLogicalDevice().createCommandPool(createInfo);
}

void CommandPool::destroy(LogicalDevice &logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyCommandPool(m_commandPool, nullptr);
}