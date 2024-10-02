//
// Created by Michael Ferents on 21/03/2022.
//

#include "DescriptorSetImage.h"

void DescriptorSetImage::write(LogicalDevice &logicalDevice, std::vector<DescriptorImage>& descriptorImage)
{
    std::vector<vk::WriteDescriptorSet> descriptorWrites {};

    for(auto& image : descriptorImage)
    {
        vk::DescriptorImageInfo descriptorImageInfo {};
        // TODO: to be changed
        descriptorImageInfo.imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
        descriptorImageInfo.imageView = image.getImageView();
        descriptorImageInfo.sampler = image.getSampler();

        vk::WriteDescriptorSet write {};
        write.dstSet = m_descriptorSet;
        write.dstBinding = image.getBinding();
        // to be changed
        write.dstArrayElement = 0;
        write.descriptorType = image.getType();
        write.descriptorCount = 1;
        write.pImageInfo = &descriptorImageInfo;

        descriptorWrites.push_back(write);
    }

    logicalDevice.getLogicalDevice().updateDescriptorSets(static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

}