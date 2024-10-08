//
// Created by Michael Ferents on 14/03/2022.
//

#include "Buffer.h"

void Buffer::destroy(LogicalDevice& logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyBuffer(m_buffer);
    logicalDevice.getLogicalDevice().freeMemory(m_deviceMemory);
}