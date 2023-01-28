//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_DESCRIPTORSETUNIFORMBUFFER_H
#define WUU_DESCRIPTORSETUNIFORMBUFFER_H
#include "DescriptorSet.h"
#include "DescriptorUniformBuffer.h"
#include "DescriptorSetUniformBuffer.h"

namespace Wuu::Vulkan {

    class DescriptorSetUniformBuffer : public DescriptorSet {
    public:

        DescriptorSetUniformBuffer() : DescriptorSet() {}

        template<typename T>
        void write(LogicalDevice& logicalDevice, DescriptorUniformBuffer<T>& descriptorUniformBuffer);

    };

}


#endif //WUU_DESCRIPTORSETUNIFORMBUFFER_H
