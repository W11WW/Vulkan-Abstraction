//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_DESCRIPTORSETIMAGE_H
#define WUU_DESCRIPTORSETIMAGE_H
#include "DescriptorSet.h"
#include "DescriptorImage.h"

namespace Wuu::Vulkan {

    class DescriptorSetImage : public DescriptorSet {
    public:

        DescriptorSetImage() : DescriptorSet() {}

        void write(LogicalDevice& logicalDevice, std::vector<DescriptorImage>& descriptorImage);

    };

}


#endif //WUU_DESCRIPTORSETIMAGE_H
