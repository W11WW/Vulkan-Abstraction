//
// Created by Michael Ferents on 23/03/2022.
//

#include "UIRenderer.h"

using namespace Wuu::Vulkan;

void UIRenderer::initialize(GLFWwindow* window)
{
    initializeRenderer(window);

    auto semaphoreCreateInfo = vk::SemaphoreCreateInfo {};

    m_imageAvailableSemaphore = m_logicalDevice.getLogicalDevice().createSemaphore(semaphoreCreateInfo);
    m_renderFinishedSemaphore = m_logicalDevice.getLogicalDevice().createSemaphore(semaphoreCreateInfo);

    m_commandPool.setPool(m_logicalDevice, static_cast<const uint32_t&&>(m_logicalDevice.getGraphicsQueueIndex()));
}

UIRenderer::~UIRenderer()
{
    m_logicalDevice.getLogicalDevice().waitIdle();

    m_commandPool.destroy(m_logicalDevice);

    m_logicalDevice.getLogicalDevice().destroySemaphore(m_imageAvailableSemaphore);
    m_logicalDevice.getLogicalDevice().destroySemaphore(m_renderFinishedSemaphore);

    m_swapchain.destroy(m_logicalDevice);
    m_logicalDevice.destroy();
    m_surface.destroy(m_instance);
    m_instance.destroy();
}

bool UIRenderer::render(GLFWwindow *window)
{
    // get image index and when we get the image make m_imageAvailableSemaphore true
    uint32_t imageIndex = 0;

    // Checks incase we have resized the window that way we can create a swapchain with images that match the size of the new window
    try {
        vk::ResultValue result = m_logicalDevice.getLogicalDevice().acquireNextImageKHR(m_swapchain.getSwapchain(),
                                                                                        std::numeric_limits<uint64_t>::max(), m_imageAvailableSemaphore, {});
        imageIndex = result.value;
    } catch (vk::OutOfDateKHRError& err) {
        recreateSwapchain(window);
        return false;
    }

    vk::PipelineStageFlags waitStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;

    // this seems very bad for performance : /
    std::vector<vk::CommandBuffer> cmdBuffers {};

    for(auto& commandBufferPair : m_commandBuffers)
    {
        cmdBuffers.push_back(commandBufferPair[imageIndex].getCommandBuffer());
    }

    // when m_imageAvailableSemaphore is true submit for rendering through command buffers and then notify m_renderFinishedSemaphore true when rendering is done on image
    auto submitInfo = vk::SubmitInfo { 1, &m_imageAvailableSemaphore, &waitStageMask, 2,
                                       cmdBuffers.data(), 1, &m_renderFinishedSemaphore };

    m_graphicsQueue.getQueue().submit(submitInfo, {});

    // when m_renderFinishedSemaphore is true and its been rendered onto an image present that image to the screen
    auto presentInfo = vk::PresentInfoKHR { 1, &m_renderFinishedSemaphore, 1,
                                            &m_swapchain.getSwapchain(), &imageIndex };

    // Checks incase we have resized the window that way we can create a swapchain with images that match the size of the new window
    try {
        auto result = m_presentQueue.getQueue().presentKHR(presentInfo);
    } catch (vk::OutOfDateKHRError& err) {
        recreateSwapchain(window);
        return false;
    }

    m_logicalDevice.getLogicalDevice().waitIdle();
    return true;
}

void UIRenderer::recreateSwapchain(GLFWwindow *window)
{
    m_logicalDevice.getLogicalDevice().waitIdle();

    m_swapchain.destroy(m_logicalDevice);

    m_swapchain.initializeSwapchain(window, m_logicalDevice, m_physicalDevice, m_surface);
}