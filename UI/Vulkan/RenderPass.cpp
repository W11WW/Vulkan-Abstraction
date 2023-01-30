//
// Created by Michael Ferents on 30/01/2023.
//

#include "RenderPass.h"
using namespace Wuu::Vulkan;

void RenderPass::initialize(LogicalDevice& logicalDevice, Swapchain& swapchain, DepthImage& depthImage)
{
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

void RenderPass::destroy(LogicalDevice& logicalDevice)
{
    for(auto& frameBuffer : m_frameBuffers)
    {
        logicalDevice.getLogicalDevice().destroyFramebuffer(frameBuffer);
    }

    logicalDevice.getLogicalDevice().destroyRenderPass(m_renderPass);
}