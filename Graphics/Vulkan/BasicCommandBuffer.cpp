//
// Created by Michael Ferents on 24/03/2022.
//

#include "BasicCommandBuffer.h"

void BasicCommandBuffer::beginCommandBufferRecord()
{
    auto beginInfo = vk::CommandBufferBeginInfo {};
    m_commandBuffer.begin(beginInfo);
}

void BasicCommandBuffer::bindRenderPass(RenderPass &renderPass, Swapchain &swapchain, int index)
{
    std::array<vk::ClearValue, 2> clearValues {};
    std::array<float, 4> color = { 0.0f, 0.0f, 0.0f, 0.0f };
    clearValues[0].color = vk::ClearColorValue(color);
    clearValues[1].depthStencil = vk::ClearDepthStencilValue(1.0f, 0);

    auto renderPassBeginInfo = vk::RenderPassBeginInfo { renderPass.getRenderPass(), renderPass.getFrameBuffers()[index],
                                                         vk::Rect2D {{0,0}, swapchain.getExtent()}, static_cast<uint32_t>(clearValues.size()), clearValues.data()};

    m_commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
}

void BasicCommandBuffer::bindPipeline(Pipeline &pipeline)
{
    m_commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getPipeline());
}

void BasicCommandBuffer::bindShape(Mesh &shape)
{
    vk::Buffer vertexBuffers[] = { shape.getVertexBuffer().getBuffer() };
    vk::DeviceSize offsets[] = {0};

    m_commandBuffer.bindVertexBuffers(0, 1, vertexBuffers, offsets);
    m_commandBuffer.bindIndexBuffer(shape.getIndexBuffer().getBuffer(), 0, vk::IndexType::eUint32);
}

void BasicCommandBuffer::bindDescriptorSets(Pipeline &pipeline, std::vector<DescriptorSet> &sets)
{
    m_commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.getPipelineLayout(), 0, 1, &sets[0].getDescriptorSet(), 0, nullptr);
    m_commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline.getPipelineLayout(), 1, 1, &sets[1].getDescriptorSet(), 0, nullptr);
}

void BasicCommandBuffer::drawIndexed(Pipeline &pipeline, Mesh &shape, glm::vec3 &position)
{
    PushConstantData data {};
    createPushConstantObject(data, position);

    m_commandBuffer.pushConstants(pipeline.getPipelineLayout(), vk::ShaderStageFlagBits::eVertex, 0, sizeof(PushConstantData), &data);
    m_commandBuffer.drawIndexed(shape.getIndexBuffer().getIndicesSize(), 1, 0, 0, 0);
}

void BasicCommandBuffer::unbindRenderPass()
{
    m_commandBuffer.endRenderPass();
}

void BasicCommandBuffer::endCommandBufferRecord()
{
    m_commandBuffer.end();
}