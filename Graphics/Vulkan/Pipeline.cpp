//
// Created by Michael Ferents on 14/03/2022.
//

#include "Pipeline.h"

template<typename VertexType, typename PushConstantType>
void Pipeline::initialize(GLFWwindow *window, LogicalDevice &logicalDevice, Swapchain &swapchain, DepthImage &depthImage, std::vector<DescriptorType>& descriptorTypes, RenderPass& renderPass)
{

    std::vector<vk::PipelineShaderStageCreateInfo> pipelineShaderStages;

    for(auto& module : m_shaderModules)
    {
        pipelineShaderStages.push_back(vk::PipelineShaderStageCreateInfo{{},
                                                                         module.getShaderStage(), module.getModule(), module.getEntryPointName().c_str()});
    }

    auto bindingDescription = VertexType::getBindingDescription();
    auto attributeDescription = VertexType::getAttributeDescriptions();

    vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo {};
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = attributeDescription.size();
    vertexInputStateCreateInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescription.data();

    auto inputAssembly =
            vk::PipelineInputAssemblyStateCreateInfo { {}, vk::PrimitiveTopology::eTriangleList, false };

    int width,height;
    glfwGetFramebufferSize(window, &width, &height);

    auto viewport =
            vk::Viewport{ 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f };

    auto scissor = vk::Rect2D{ {0,0}, swapchain.getExtent() };

    auto viewportState = vk::PipelineViewportStateCreateInfo { {}, 1, &viewport, 1, &scissor };

    auto rasterizer = vk::PipelineRasterizationStateCreateInfo{{}, false,
                                                               false, vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack,
                                                               vk::FrontFace::eCounterClockwise, {}, {}, {}, {}, 1.0f};

    auto multisampling = vk::PipelineMultisampleStateCreateInfo{{}, vk::SampleCountFlagBits::e1, false, 1.0};

    auto colorBlendAttachment = vk::PipelineColorBlendAttachmentState{ {}, vk::BlendFactor::eOne,
                                                                       vk::BlendFactor::eZero, vk::BlendOp::eAdd,
                                                                       vk::BlendFactor::eOne, vk::BlendFactor::eZero,
                                                                       vk::BlendOp::eAdd,
                                                                       vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                                                                       vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA };

    auto colorBlending = vk::PipelineColorBlendStateCreateInfo { {}, false,
                                                                 vk::LogicOp::eCopy, 1, &colorBlendAttachment };

    vk::PipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo {};
    depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthCompareOp = vk::CompareOp::eLess;
    depthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
    depthStencilStateCreateInfo.stencilTestEnable = VK_TRUE;

    std::vector<vk::DescriptorSetLayoutBinding> descriptorBindings;

    for(auto& type : descriptorTypes)
    {
        vk::DescriptorSetLayoutBinding layoutBinding {};
        layoutBinding.binding = type.getBinding();
        layoutBinding.descriptorCount = 1;
        layoutBinding.descriptorType = type.getType();
        // this is prob dumb
        if(type.getType() == vk::DescriptorType::eCombinedImageSampler)
        {
            layoutBinding.pImmutableSamplers = nullptr;
        }
        layoutBinding.stageFlags = type.getShaderStage();

        descriptorBindings.push_back(layoutBinding);
    }

    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfoOne {};
    descriptorSetLayoutCreateInfoOne.bindingCount = 1;
    descriptorSetLayoutCreateInfoOne.pBindings = &descriptorBindings[0];

    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfoTwo {};
    descriptorSetLayoutCreateInfoTwo.bindingCount = 1;
    descriptorSetLayoutCreateInfoTwo.pBindings = &descriptorBindings[1];

    m_descriptorSetLayout.resize(2);

    m_descriptorSetLayout[0] = logicalDevice.getLogicalDevice().createDescriptorSetLayout(descriptorSetLayoutCreateInfoOne);
    m_descriptorSetLayout[1] = logicalDevice.getLogicalDevice().createDescriptorSetLayout(descriptorSetLayoutCreateInfoTwo);

    vk::PushConstantRange pushConstantRange {};
    pushConstantRange.stageFlags = vk::ShaderStageFlagBits::eVertex;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(PushConstantType);

    vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
    pipelineLayoutCreateInfo.setLayoutCount = 2;
    pipelineLayoutCreateInfo.pSetLayouts = m_descriptorSetLayout.data();
    pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
    pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;


    m_pipelineLayout = logicalDevice.getLogicalDevice().createPipelineLayout(pipelineLayoutCreateInfo);

    auto pipelineCreateInfo = vk::GraphicsPipelineCreateInfo { {}, 2, pipelineShaderStages.data(),
                                                               &vertexInputStateCreateInfo, &inputAssembly, nullptr,
                                                               &viewportState, &rasterizer, &multisampling, &depthStencilStateCreateInfo,
                                                               &colorBlending, nullptr, m_pipelineLayout, renderPass.getRenderPass(), 0};

    m_pipeline = logicalDevice.getLogicalDevice().createGraphicsPipeline({}, pipelineCreateInfo).value;

}

void Pipeline::destroy(LogicalDevice& logicalDevice)
{
    logicalDevice.getLogicalDevice().destroyPipeline(m_pipeline);
    logicalDevice.getLogicalDevice().destroyPipelineLayout(m_pipelineLayout);
}

template void Pipeline::initialize<Vertex, PushConstantData>(GLFWwindow *window, LogicalDevice &logicalDevice, Swapchain &swapchain, DepthImage &depthImage, std::vector<DescriptorType>& descriptorTypes, RenderPass& renderPass);