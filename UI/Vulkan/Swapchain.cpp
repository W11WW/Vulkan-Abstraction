//
// Created by Michael Ferents on 11/03/2022.
//

#include "Swapchain.h"

using namespace Wuu::Vulkan;

void Swapchain::initializeSwapchain(GLFWwindow *window, LogicalDevice &logicalDevice, PhysicalDevice &physicalDevice, const Surface &surface)
{
    std::set<uint32_t> uniqueQueueFamilyIndices = { static_cast<uint32_t>(logicalDevice.getGraphicsQueueIndex()),
                                                    static_cast<uint32_t>(logicalDevice.getPresentQueueIndex()) };

    std::vector<uint32_t> FamilyIndices = { uniqueQueueFamilyIndices.begin(),
                                            uniqueQueueFamilyIndices.end() };

    struct SM {
        vk::SharingMode sharingMode;
        uint32_t  familyIndicesCount;
        uint32_t* familyIndicesDataPtr;
    } sharingModeUtil {(logicalDevice.getGraphicsQueueIndex() != logicalDevice.getPresentQueueIndex()) ?
    SM{ vk::SharingMode::eConcurrent, 2u, FamilyIndices.data() } :
    SM{ vk::SharingMode::eExclusive, 0u, static_cast<uint32_t*>(nullptr) } };

    auto capabilities = physicalDevice.getPhysicalDevice().getSurfaceCapabilitiesKHR(surface.getSurface());
    auto format = vk::Format::eB8G8R8A8Unorm;
    auto formats = physicalDevice.getPhysicalDevice().getSurfaceFormatsKHR(surface.getSurface());

    int width,height;
    glfwGetFramebufferSize(window, &width, &height);

    auto extent = vk::Extent2D{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

    vk::SwapchainCreateInfoKHR swapchainCreateInfo({}, surface.getSurface(), static_cast<uint32_t>(m_numbOfImages), format,
                                                   vk::ColorSpaceKHR::eSrgbNonlinear, extent, 1, vk::ImageUsageFlagBits::eColorAttachment,
                                                   sharingModeUtil.sharingMode, sharingModeUtil.familyIndicesCount,
                                                   sharingModeUtil.familyIndicesDataPtr, vk::SurfaceTransformFlagBitsKHR::eIdentity,
                                                   vk::CompositeAlphaFlagBitsKHR::eOpaque, vk::PresentModeKHR::eFifo, true, nullptr);

    m_swapchain = logicalDevice.getLogicalDevice().createSwapchainKHR(swapchainCreateInfo);

    auto m_swapchainImagesVk = logicalDevice.getLogicalDevice().getSwapchainImagesKHR(m_swapchain);
    for(auto& image : m_swapchainImagesVk)
    {
        SwapchainImage imageTemp {};
        imageTemp.setImage(image, logicalDevice, format);
        m_swapchainImages.push_back(imageTemp);

    }

    m_extent = extent;
    m_format = format;

}

void Swapchain::destroy(LogicalDevice &logicalDevice)
{
    for(auto& image : m_swapchainImages)
    {
        image.destroy(logicalDevice);
    }
    m_swapchainImages.resize(0);
    logicalDevice.getLogicalDevice().destroySwapchainKHR(m_swapchain, nullptr);
}