//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_DESCRIPTORUNIFORMBUFFER_H
#define WUU_DESCRIPTORUNIFORMBUFFER_H
#include "Buffer.h"
#include "DescriptorType.h"
#include "Swapchain.h"
#include "MemoryFunctions.h"
#include "DescriptorFunctions.h"
#include "UI/Element.h"
#include "UniformBufferType.h"

// TODO: change so it saves data on multiple elements

namespace Wuu::Vulkan {

    template<typename T>
    class DescriptorUniformBuffer : public Buffer, public DescriptorType {
    public:

        using UniformBufferObject = T;

        DescriptorUniformBuffer() : Buffer(), DescriptorType() {}

        virtual void initialize(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice);

        virtual inline void updateUniformBuffer(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, Swapchain& swapchain);

        auto& getBufferInfo() noexcept { return m_bufferInfo; }

    protected:

        vk::DescriptorBufferInfo m_bufferInfo;

    };

}


#endif //WUU_DESCRIPTORUNIFORMBUFFER_H
