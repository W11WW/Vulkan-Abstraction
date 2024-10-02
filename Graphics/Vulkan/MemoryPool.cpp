//
// Created by Michael Ferents on 12/03/2022.
//

#include "MemoryPool.h"

void MemoryPool::initialize(LogicalDevice &logicalDevice, PhysicalDevice &physicalDevice, const uint32_t transferQueueFamilyIndex)
{
    m_commandPool.setPool(logicalDevice, std::move(transferQueueFamilyIndex));
    m_queue.setQueue(logicalDevice, std::move(transferQueueFamilyIndex));
}