//
// Created by Michael Ferents on 30/01/2023.
//

#ifndef WUU_RENDERPASS_H
#define WUU_RENDERPASS_H
#include <vulkan/vulkan.hpp>
#include <vector>

#include "LogicalDevice.h"
#include "Swapchain.h"
#include "DepthImage.h"

namespace Wuu::Vulkan {

    class RenderPass {
    public:

        RenderPass() = default;

        void initialize(LogicalDevice& logicalDevice, Swapchain& swapchain, DepthImage& depthImage);
        void destroy(LogicalDevice& logicalDevice);

        [[nodiscard]] inline auto& getRenderPass() noexcept { return m_renderPass; }
        [[nodiscard]] inline auto& getFrameBuffers() noexcept { return m_frameBuffers; }

    private:

        vk::RenderPass m_renderPass;
        std::vector<vk::Framebuffer> m_frameBuffers;

    };

}


#endif //WUU_RENDERPASS_H
