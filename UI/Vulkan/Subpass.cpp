//
// Created by Michael Ferents on 07/02/2023.
//

#include "Subpass.h"

using namespace Wuu::Vulkan;

void Subpass::setDescription() noexcept
{
    vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);
    vk::AttachmentReference depthAttachmentRef(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

    m_subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    m_subpassDescription.colorAttachmentCount = 1;
    m_subpassDescription.pColorAttachments = &colorAttachmentRef;
    m_subpassDescription.pDepthStencilAttachment = &depthAttachmentRef;

    m_subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    m_subpassDependency.dstSubpass = 0;
    m_subpassDependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    m_subpassDependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    m_subpassDependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;
}