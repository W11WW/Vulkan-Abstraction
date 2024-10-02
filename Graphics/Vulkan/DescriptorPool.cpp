//
// Created by Michael Ferents on 14/03/2022.
//

#include "DescriptorPool.h"

void DescriptorPool::setPool(LogicalDevice &logicalDevice, size_t uniformBufferSize, size_t imageSamplerSize, size_t setCount)
{
    auto poolSizeUniformBuffer = vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer, uniformBufferSize);
    auto poolSizeImageSampler = vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler, imageSamplerSize);

    std::array<vk::DescriptorPoolSize, 2> poolSizes = { poolSizeUniformBuffer, poolSizeImageSampler };

    auto poolInfo = vk::DescriptorPoolCreateInfo(vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet, 10, setCount, poolSizes.data());
    m_descriptorPool = logicalDevice.getLogicalDevice().createDescriptorPool(poolInfo);

    m_uniformBufferSize = uniformBufferSize;
    m_imageSamplerSize = imageSamplerSize;
    m_setCount = setCount;
}

void DescriptorPool::destroy(LogicalDevice &logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyDescriptorPool(m_descriptorPool);
}