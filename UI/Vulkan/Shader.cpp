//
// Created by Michael Ferents on 14/03/2022.
//

#include "Shader.h"

using namespace Wuu::Vulkan;

template<typename T>
void Shader<T>::setPath(std::string_view vertPath, std::string_view fragPath)
{
    m_vertShaderPath = vertPath;
    m_fragShaderPath = fragPath;
}

template<typename T>
void Shader<T>::initialize(GLFWwindow *window, LogicalDevice &logicalDevice, Swapchain &swapchain, DepthImage &depthImage, std::vector<DescriptorType>& descriptorTypes)
{
    auto vertShaderCode = readFile(m_vertShaderPath.data());
    auto vertShaderCreateInfo =
            vk::ShaderModuleCreateInfo{{}, vertShaderCode.size(),
                                       reinterpret_cast<const uint32_t *>(vertShaderCode.data())};
    auto vertexShaderModule = logicalDevice.getLogicalDevice().createShaderModule(vertShaderCreateInfo);

    auto fragShaderCode = readFile(m_fragShaderPath.data());
    auto fragShaderCreateInfo =
            vk::ShaderModuleCreateInfo{{}, fragShaderCode.size(),
                                       reinterpret_cast<const uint32_t *>(fragShaderCode.data())};
    auto fragmentShaderModule = logicalDevice.getLogicalDevice().createShaderModule(fragShaderCreateInfo);

    auto vertShaderStageInfo = vk::PipelineShaderStageCreateInfo{{},
                                                                 vk::ShaderStageFlagBits::eVertex, vertexShaderModule, "main"};

    auto fragShaderStageInfo = vk::PipelineShaderStageCreateInfo{{},
                                                                 vk::ShaderStageFlagBits::eFragment, fragmentShaderModule, "main"};

    auto pipelineShaderStages =
            std::vector<vk::PipelineShaderStageCreateInfo> { vertShaderStageInfo, fragShaderStageInfo };

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

    /*
    vk::DescriptorSetLayoutBinding descriptorSetLayoutBinding {};
    descriptorSetLayoutBinding.binding = 0;
    descriptorSetLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
    descriptorSetLayoutBinding.descriptorCount = 1;
    descriptorSetLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;

    vk::DescriptorSetLayoutBinding samplerLayoutBinding {};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = vk::DescriptorType::eCombinedImageSampler;
    samplerLayoutBinding.pImmutableSamplers = nullptr;
    samplerLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eFragment;

    std::array<vk::DescriptorSetLayoutBinding, 2> bindings = { descriptorSetLayoutBinding, samplerLayoutBinding };

    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo {};
    descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    descriptorSetLayoutCreateInfo.pBindings = bindings.data();

    m_descriptorSetLayout = logicalDevice.getLogicalDevice().createDescriptorSetLayout(descriptorSetLayoutCreateInfo);

     */

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

    vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
    pipelineLayoutCreateInfo.setLayoutCount = 2;
    pipelineLayoutCreateInfo.pSetLayouts = m_descriptorSetLayout.data();

    m_pipelineLayout = logicalDevice.getLogicalDevice().createPipelineLayout(pipelineLayoutCreateInfo);

    vk::AttachmentDescription colorAttachment {};
    colorAttachment.format = swapchain.getFormat();
    colorAttachment.samples = vk::SampleCountFlagBits::e1;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentDescription depthAttachment {};
    depthAttachment.format = vk::Format::eD32Sfloat;
    depthAttachment.samples = vk::SampleCountFlagBits::e1;
    depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    depthAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
    depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

    vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);
    vk::AttachmentReference depthAttachmentRef(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

    vk::SubpassDescription subpass;
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    vk::SubpassDependency dependency {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;
    std::array<vk::AttachmentDescription, 2> attachments = { {colorAttachment, depthAttachment} };

    m_renderPass = logicalDevice.getLogicalDevice().createRenderPass(vk::RenderPassCreateInfo{{}, 2, attachments.data(), 1, &subpass, 1, &dependency});

    auto pipelineCreateInfo = vk::GraphicsPipelineCreateInfo { {}, 2, pipelineShaderStages.data(),
                                                               &vertexInputStateCreateInfo, &inputAssembly, nullptr,
                                                               &viewportState, &rasterizer, &multisampling, &depthStencilStateCreateInfo,
                                                               &colorBlending, nullptr, m_pipelineLayout, m_renderPass, 0};

    m_pipeline = logicalDevice.getLogicalDevice().createGraphicsPipeline({}, pipelineCreateInfo).value;

    m_frameBuffers.resize(swapchain.getSize());

    for(size_t i = 0; i < swapchain.getSize(); i++)
    {
        std::array<vk::ImageView, 2> attachments = {
                (swapchain.getImage()[i].getImageView()),
                depthImage.getImageView()
        };

        m_frameBuffers[i] = logicalDevice.getLogicalDevice().createFramebuffer(vk::FramebufferCreateInfo {
                {}, m_renderPass, static_cast<uint32_t>(attachments.size()), attachments.data(),
                swapchain.getExtent().width, swapchain.getExtent().height, 1
        });
    }

}

template<typename T>
void Shader<T>::destroy(LogicalDevice& logicalDevice)
{
    for(auto& frameBuffer : m_frameBuffers)
    {
        logicalDevice.getLogicalDevice().destroyFramebuffer(frameBuffer);
    }

    logicalDevice.getLogicalDevice().destroyPipeline(m_pipeline);
    logicalDevice.getLogicalDevice().destroyPipelineLayout(m_pipelineLayout);
    logicalDevice.getLogicalDevice().destroyRenderPass(m_renderPass);
}

template class Wuu::Vulkan::Shader<Vertex>;