//
// Created by Michael Ferents on 30/01/2023.
//

#include "RenderPass.h"
using namespace Wuu::Vulkan;

void RenderPass::initialize(LogicalDevice& logicalDevice, Swapchain& swapchain, DepthImage& depthImage)
{
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