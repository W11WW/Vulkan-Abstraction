//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_SWAPCHAIN_H
#define WUU_SWAPCHAIN_H
#include "Surface.h"
#include "SwapchainImage.h"

namespace Wuu::Vulkan {

    class Swapchain {
    public:

        explicit Swapchain(const uint32_t&& numbOfImages = 2) : m_numbOfImages(numbOfImages) {}

        virtual void initializeSwapchain(GLFWwindow* window, LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice,  const Surface& surface);
        virtual void destroy(LogicalDevice& logicalDevice);

        [[nodiscard]] const auto& getFormat() const noexcept { return m_format; }
        [[nodiscard]] const auto& getExtent() const noexcept { return m_extent; }
        [[nodiscard]] auto& getSwapchain() noexcept { return m_swapchain; }
        [[nodiscard]] auto getSize() noexcept { return m_numbOfImages; }
        [[nodiscard]] auto& getImage() noexcept { return m_swapchainImages; }

    protected:

        vk::SwapchainKHR m_swapchain;
        vk::Format m_format;
        vk::Extent2D m_extent;

        std::vector<SwapchainImage> m_swapchainImages;

        uint32_t m_numbOfImages;

    };

}


#endif //WUU_SWAPCHAIN_H
