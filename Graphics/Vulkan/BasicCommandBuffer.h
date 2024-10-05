//
// Created by Michael Ferents on 24/03/2022.
//

#ifndef WUU_UICOMMANDBUFFER_H
#define WUU_UICOMMANDBUFFER_H
#include "CommandBuffer.h"
#include "DescriptorSetUniformBuffer.h"
#include "DescriptorSetImage.h"
#include "PushConstantFunctions.h"
#include "Pipeline.h"
#include "Mesh.h"

class BasicCommandBuffer : public CommandBuffer {
public:

    BasicCommandBuffer() = default;

    void beginCommandBufferRecord() final;
    void endCommandBufferRecord() final;

    void bindRenderPass(RenderPass& renderPass, Swapchain& swapchain, int index);
    void bindPipeline(Pipeline& pipeLine);
    void bindShape(Mesh& shape);
    void bindDescriptorSets(Pipeline& pipeLine, std::vector<DescriptorSet>& descriptorsets);
    void drawIndexed(Pipeline& pipeLine, Mesh& shape, glm::vec3& position);
    void unbindRenderPass();

};

#endif //WUU_UICOMMANDBUFFER_H
