//
// Created by Michael Ferents on 21/03/2022.
//

#include "DescriptorSetUniformBuffer.h"

template<typename T>
void DescriptorSetUniformBuffer::write(LogicalDevice& logicalDevice, DescriptorUniformBuffer<T>& descriptorUniformBuffer)
{

    vk::WriteDescriptorSet write {};
    write.dstSet = m_descriptorSet;
    write.dstBinding = descriptorUniformBuffer.getBinding();
        // to be changed
    write.dstArrayElement = 0;
    write.descriptorType = descriptorUniformBuffer.getType();
    write.descriptorCount = 1;
    write.pBufferInfo = &descriptorUniformBuffer.getBufferInfo();

    logicalDevice.getLogicalDevice().updateDescriptorSets(static_cast<uint32_t>(1), &write, 0, nullptr);

}

template void DescriptorSetUniformBuffer::write<UniformBufferObject>(LogicalDevice &logicalDevice, DescriptorUniformBuffer<UniformBufferObject> &descriptorUniformBuffer);