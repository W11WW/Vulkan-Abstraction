//
// Created by Michael Ferents on 14/03/2022.
//

#include "DescriptorImage.h"

using namespace Wuu::Vulkan;

void DescriptorImage::setImage(LogicalDevice &logicalDevice, PhysicalDevice &physicalDevice, MemoryPool &memoryPool, std::string fileName)
{

    createDescriptorImage(logicalDevice, physicalDevice, memoryPool, m_image, m_deviceMemory, fileName);

    vk::ImageViewCreateInfo imageViewCreateInfo {};
    imageViewCreateInfo.image = m_image;
    imageViewCreateInfo.viewType = vk::ImageViewType::e2D;
    imageViewCreateInfo.format = vk::Format::eR8G8B8A8Srgb;
    imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    m_imageView = logicalDevice.getLogicalDevice().createImageView(imageViewCreateInfo);

    vk::SamplerCreateInfo samplerCreateInfo {};
    samplerCreateInfo.magFilter = vk::Filter::eLinear;
    samplerCreateInfo.minFilter = vk::Filter::eLinear;
    samplerCreateInfo.addressModeU = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.addressModeV = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.addressModeW = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.anisotropyEnable = VK_TRUE;

    vk::PhysicalDeviceProperties physicalDeviceProperties {};
    physicalDeviceProperties = physicalDevice.getPhysicalDevice().getProperties();

    samplerCreateInfo.maxAnisotropy = physicalDeviceProperties.limits.maxSamplerAnisotropy;
    samplerCreateInfo.borderColor = vk::BorderColor::eIntOpaqueBlack;
    samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
    samplerCreateInfo.compareEnable = VK_FALSE;
    samplerCreateInfo.compareOp = vk::CompareOp::eAlways;
    samplerCreateInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
    samplerCreateInfo.mipLodBias = 0.0f;
    samplerCreateInfo.minLod = 0.0f;
    samplerCreateInfo.maxLod = 0.0f;

    m_sampler = logicalDevice.getLogicalDevice().createSampler(samplerCreateInfo);

}