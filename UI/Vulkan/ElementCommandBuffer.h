//
// Created by Michael Ferents on 24/03/2022.
//

#ifndef WUU_ELEMENTCOMMANDBUFFER_H
#define WUU_ELEMENTCOMMANDBUFFER_H
#include "CommandBuffer.h"
#include "DescriptorSetUniformBuffer.h"
#include "DescriptorSetImage.h"
#include "PipeLine.h"
#include "UI/Element.h"
#include "Shape.h"

namespace Wuu::Vulkan
{
    class ElementCommandBuffer : public CommandBuffer {
    public:

        ElementCommandBuffer() = default;

        void beginCommandBufferRecord() final;
        void endCommandBufferRecord() final;
        void recordElement(PipeLine& pipeline, RenderPass& renderPass, Element& element, std::vector<vk::DescriptorSet>& sets, Shape& shape, int index, Swapchain& swapchain);

    };
}


#endif //WUU_ELEMENTCOMMANDBUFFER_H
