//
// Created by Michael Ferents on 14/03/2022.
//

#include "DescriptorUniformBuffer.h"

template<typename T>
void DescriptorUniformBuffer<T>::initialize(LogicalDevice &logicalDevice, PhysicalDevice &physicalDevice)
{

    createBuffer(logicalDevice, physicalDevice, sizeof(UniformBufferObject), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostCoherent |
    vk::MemoryPropertyFlagBits::eHostVisible, m_buffer, m_deviceMemory);

    m_bufferInfo = vk::DescriptorBufferInfo(m_buffer, 0, sizeof(UniformBufferObject));
}

template<typename T>
void DescriptorUniformBuffer<T>::updateUniformBuffer(LogicalDevice &logicalDevice, PhysicalDevice& physicalDevice, Swapchain &swapchain)
{


    T ubo {};
    createUniformBufferObject(ubo, swapchain);

    void* data;
    logicalDevice.getLogicalDevice().mapMemory(m_deviceMemory, 0, sizeof(UniformBufferObject), vk::MemoryMapFlags(), &data);
    memcpy(data, &ubo, sizeof(UniformBufferObject));
    logicalDevice.getLogicalDevice().unmapMemory(m_deviceMemory);

}

template class DescriptorUniformBuffer<UniformBufferObject>;