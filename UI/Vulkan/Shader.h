//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_SHADER_H
#define WUU_SHADER_H
#include "Swapchain.h"
#include "LogicalDevice.h"
#include "DepthImage.h"
#include "DescriptorType.h"
#include "Utils.h"
#include <vector>
#include "VertexTypes.h"

// TODO: eventually change it so it accepts different viewports and descriptor rules

namespace Wuu::Vulkan {

    template<typename T>
    class Shader {

    public:
        using VertexType = T;

        Shader() = default;

        virtual void destroy(LogicalDevice& logicalDevice);
        virtual void initialize(GLFWwindow* window, LogicalDevice& logicalDevice, Swapchain& swapchain, DepthImage& depthImage, std::vector<DescriptorType>& descriptorTypes);
        virtual void setPath(std::string_view vertPath, std::string_view fragPath);

        [[nodiscard]] inline auto& getRenderPass() noexcept { return m_renderPass; }
        [[nodiscard]] inline auto& getPipeline() noexcept { return m_pipeline; }
        [[nodiscard]] inline auto& getFrameBuffers() noexcept { return m_frameBuffers; }
        [[nodiscard]] auto& getPipelineLayout() noexcept { return m_pipelineLayout; }
        [[nodiscard]] auto& getDescriptorSetLayout() noexcept { return m_descriptorSetLayout; }

    protected:

        std::string m_vertShaderPath;
        std::string m_fragShaderPath;

        vk::RenderPass m_renderPass;
        vk::Pipeline m_pipeline;
        vk::PipelineLayout m_pipelineLayout;
        std::vector<vk::DescriptorSetLayout> m_descriptorSetLayout;
        std::vector<vk::Framebuffer> m_frameBuffers;

    };

}


#endif //WUU_SHADER_H
