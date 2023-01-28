//
// Created by Michael Ferents on 13/03/2022.
//

#include "DepthImage.h"

using namespace Wuu::Vulkan;

void DepthImage::setImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, const vk::Extent2D swapchainExtent)
{
    createImage(logicalDevice, physicalDevice, swapchainExtent.width, swapchainExtent.height, vk::Format::eD32Sfloat, vk::ImageTiling::eOptimal,
                vk::ImageUsageFlagBits::eDepthStencilAttachment, vk::MemoryPropertyFlagBits::eDeviceLocal, m_image, m_deviceMemory);

    vk::ImageViewCreateInfo imageViewCreateInfo {};
    imageViewCreateInfo.image = m_image;
    imageViewCreateInfo.viewType = vk::ImageViewType::e2D;
    imageViewCreateInfo.format = vk::Format::eD32Sfloat;
    imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    m_imageView = logicalDevice.getLogicalDevice().createImageView(imageViewCreateInfo);

    transitionImageLayout(logicalDevice, memoryPool, m_image, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal);
}

// TODO: might cause problems because we aint destroying device memory

void DepthImage::destroy(LogicalDevice &logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyImageView(m_imageView);
    logicalDevice.getLogicalDevice().destroyImage(m_image);
}