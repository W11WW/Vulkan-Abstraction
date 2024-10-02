//
// Created by Michael Ferents on 12/03/2022.
//

#include "CommandBuffer.h"

void CommandBuffer::setBuffer(LogicalDevice& logicalDevice, CommandPool& commandPool, const vk::CommandBufferLevel commandBufferLevel)
{
    m_commandBuffer = logicalDevice.getLogicalDevice().allocateCommandBuffers(vk::CommandBufferAllocateInfo(commandPool.getCommandPool(), commandBufferLevel, 1)).front();
}

void CommandBuffer::destroy(LogicalDevice& logicalDevice, CommandPool& commandPool)
{
    logicalDevice.getLogicalDevice().freeCommandBuffers(commandPool.getCommandPool(), m_commandBuffer);
}