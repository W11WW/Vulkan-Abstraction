//
// Created by Michael Ferents on 13/03/2022.
//

#ifndef WUU_DEPTHIMAGE_H
#define WUU_DEPTHIMAGE_H

#include "Image.h"
#include "MemoryFunctions.h"

namespace Wuu::Vulkan {

    class DepthImage : public Image {
    public:

        DepthImage() = default;

        void setImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, const vk::Extent2D swapchainExtent);

        void destroy(LogicalDevice& logicalDevice) override;

    };

}


#endif //WUU_DEPTHIMAGE_H
