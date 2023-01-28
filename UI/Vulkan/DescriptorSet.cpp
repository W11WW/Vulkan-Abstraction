//
// Created by Michael Ferents on 17/03/2022.
//

#include "DescriptorSet.h"
using namespace Wuu::Vulkan;

void DescriptorSet::initialize(LogicalDevice& logicalDevice, DescriptorPool& pool, vk::DescriptorSetLayout& layout)
{
    auto descriptorSetInfo = vk::DescriptorSetAllocateInfo(pool.getPool(), 1, &layout);
    m_descriptorSet = logicalDevice.getLogicalDevice().allocateDescriptorSets(descriptorSetInfo).front();
}