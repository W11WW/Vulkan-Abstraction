//
// Created by Michael Ferents on 11/03/2022.
//

#include "Image.h"

void Image::destroy(LogicalDevice &logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyImageView(m_imageView, nullptr);
    logicalDevice.getLogicalDevice().freeMemory(m_deviceMemory);
}