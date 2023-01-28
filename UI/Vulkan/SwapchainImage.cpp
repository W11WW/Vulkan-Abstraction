//
// Created by Michael Ferents on 13/03/2022.
//

#include "SwapchainImage.h"

using namespace Wuu::Vulkan;

void SwapchainImage::setImage(vk::Image image, LogicalDevice& logicalDevice, vk::Format format)
{
    m_image = image;

    vk::ImageViewCreateInfo imageViewCreateInfo(vk::ImageViewCreateFlags(), image,
                                                vk::ImageViewType::e2D, format,
                                                vk::ComponentMapping { vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG,
                                                                       vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA },
                                                vk::ImageSubresourceRange { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
    m_imageView = logicalDevice.getLogicalDevice().createImageView(imageViewCreateInfo);
}