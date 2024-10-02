//
// Created by Michael Ferents on 11/03/2022.
//

#include "Queue.h"

void Queue::setQueue(LogicalDevice &logicalDevice, const uint32_t queueFamilyIndex)
{
    m_queue = logicalDevice.getLogicalDevice().getQueue(static_cast<uint32_t>(queueFamilyIndex), 0);
}