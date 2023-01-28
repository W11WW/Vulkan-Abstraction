//
// Created by Michael Ferents on 13/03/2022.
//

#ifndef WUU_MEMORYCOMMANDBUFFER_H
#define WUU_MEMORYCOMMANDBUFFER_H
#include "CommandBuffer.h"

namespace Wuu::Vulkan {

    class MemoryCommandBuffer : public CommandBuffer {
    public:

        MemoryCommandBuffer() = default;

        void beginCommandBufferRecord() final;

        // TODO: research what pipeline barriers do again and what this func does in general
        void recordPipelineBarrier(vk::PipelineStageFlags sourceStage, vk::PipelineStageFlags destinationStage, vk::ImageMemoryBarrier& barrier);

        // TODO: look into what region count does in function
        void recordCopyBufferToImage(vk::Buffer& buffer, vk::Image& image, vk::ImageLayout layout, vk::BufferImageCopy& bufferImageCopy);

        void recordCopyBuffer(vk::Buffer& srcBuffer, vk::Buffer& dstBuffer, vk::BufferCopy bufferCopy);

        void endCommandBufferRecord() final;

    };

}


#endif //WUU_MEMORYCOMMANDBUFFER_H
