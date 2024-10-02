//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_PIPELINE_H
#define WUU_PIPELINE_H
#include "Swapchain.h"
#include "LogicalDevice.h"
#include "DepthImage.h"
#include "DescriptorType.h"
#include "Utils.h"
#include <vector>
#include "VertexTypes.h"
#include "PushConstantType.h"
#include "RenderPass.h"
#include "ShaderModule.h"

// TODO: eventually change it so it accepts different viewports and descriptor rules

class Pipeline {
public:

    Pipeline() = default;

    virtual void destroy(LogicalDevice &logicalDevice);

    template<typename VertexType, typename PushConstantType>
    void initialize(GLFWwindow *window, LogicalDevice &logicalDevice, Swapchain &swapchain, DepthImage &depthImage,
                    std::vector<DescriptorType> &descriptorTypes, RenderPass &renderPass);

    void addModule(ShaderModule& module) { m_shaderModules.push_back(module); };

    [[nodiscard]] inline auto &getPipeline() noexcept { return m_pipeline; }

    [[nodiscard]] auto &getPipelineLayout() noexcept { return m_pipelineLayout; }

    [[nodiscard]] auto &getDescriptorSetLayout() noexcept { return m_descriptorSetLayout; }

protected:

    vk::Pipeline m_pipeline;
    vk::PipelineLayout m_pipelineLayout;

    std::vector<vk::DescriptorSetLayout> m_descriptorSetLayout;
    std::vector<ShaderModule> m_shaderModules;
};


#endif //WUU_PIPELINE_H
