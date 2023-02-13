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

// TODO: eventually change it so it accepts different viewports and descriptor rules

namespace Wuu::Vulkan {

    class Pipeline {

    public:

        Pipeline() = default;

        virtual void destroy(LogicalDevice &logicalDevice);

        template<typename VertexType, typename PushConstantType>
        void initialize(GLFWwindow *window, LogicalDevice &logicalDevice, Swapchain &swapchain, DepthImage &depthImage,
                        std::vector<DescriptorType> &descriptorTypes, RenderPass &renderPass);

        virtual void setPath(std::string_view vertPath, std::string_view fragPath);

        [[nodiscard]] inline auto &getPipeline() noexcept { return m_pipeline; }

        [[nodiscard]] auto &getPipelineLayout() noexcept { return m_pipelineLayout; }

        [[nodiscard]] auto &getDescriptorSetLayout() noexcept { return m_descriptorSetLayout; }

    protected:

        std::string m_vertShaderPath;
        std::string m_fragShaderPath;

        vk::Pipeline m_pipeline;
        vk::PipelineLayout m_pipelineLayout;
        std::vector<vk::DescriptorSetLayout> m_descriptorSetLayout;

    };


}

#endif //WUU_PIPELINE_H
