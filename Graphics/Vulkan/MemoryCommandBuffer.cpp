//
// Created by Michael Ferents on 13/03/2022.
//

#include "MemoryCommandBuffer.h"

void MemoryCommandBuffer::beginCommandBufferRecord()
{
    auto beginInfo = vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    m_commandBuffer.begin(beginInfo);
}

void MemoryCommandBuffer::recordPipelineBarrier(vk::PipelineStageFlags sourceStage,
                                                vk::PipelineStageFlags destinationStage,
                                                vk::ImageMemoryBarrier &barrier)
{

    m_commandBuffer.pipelineBarrier(sourceStage, destinationStage, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &barrier);

}

void MemoryCommandBuffer::recordCopyBufferToImage(vk::Buffer& buffer, vk::Image& image, vk::ImageLayout layout, vk::BufferImageCopy& bufferImageCopy)
{
    m_commandBuffer.copyBufferToImage(buffer, image, layout, 1, &bufferImageCopy);
}

void MemoryCommandBuffer::recordCopyBuffer(vk::Buffer &srcBuffer, vk::Buffer &dstBuffer, vk::BufferCopy bufferCopy)
{
    m_commandBuffer.copyBuffer(srcBuffer, dstBuffer, bufferCopy);
}



void MemoryCommandBuffer::endCommandBufferRecord()
{
    m_commandBuffer.end();
}