//
// Created by Michael Ferents on 24/03/2022.
//

#include "ElementCommandBuffer.h"

using namespace Wuu::Vulkan;

void ElementCommandBuffer::beginCommandBufferRecord()
{
    auto beginInfo = vk::CommandBufferBeginInfo {};
    m_commandBuffer.begin(beginInfo);
}

void ElementCommandBuffer::recordElement(PipeLine& pipeline,
                                         RenderPass& renderPass,
                                         Element& element,
                                         std::vector<vk::DescriptorSet>& sets,
                                         Shape& shape,
                                         int index,
                                         Swapchain& swapchain)
{
    std::array<vk::ClearValue, 2> clearValues {};
    std::array<float, 4> color = { 0.0f, 0.0f, 0.0f, 0.9f };
    clearValues[0].color = vk::ClearColorValue(color);
    clearValues[1].depthStencil = vk::ClearDepthStencilValue(1.0f, 0);

    auto renderPassBeginInfo = vk::RenderPassBeginInfo { renderPass.getRenderPass(), renderPass.getFrameBuffers()[index],
                                                         vk::Rect2D {{0,0}, swapchain.getExtent()}, static_cast<uint32_t>(clearValues.size()), clearValues.data()};

    m_commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
    m_commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getPipeline());

    vk::Buffer vertexBuffers[] = { shape.getVertexBuffer().getBuffer() };
    vk::DeviceSize offsets[] = {0};

    m_commandBuffer.bindVertexBuffers(0, 1, vertexBuffers, offsets);
    m_commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.getPipelineLayout(), 0, 1, &sets[0], 0, nullptr);
    m_commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.getPipelineLayout(), 1, 1, &sets[1], 0, nullptr);
    m_commandBuffer.bindIndexBuffer(shape.getIndexBuffer().getBuffer(), 0, vk::IndexType::eUint32);
    m_commandBuffer.drawIndexed(shape.getIndexBuffer().getIndicesSize(), 1, 0, 0, 0);

    m_commandBuffer.endRenderPass();
}

void ElementCommandBuffer::endCommandBufferRecord()
{
    m_commandBuffer.end();
}