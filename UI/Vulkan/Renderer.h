//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_RENDERER_H
#define WUU_RENDERER_H
#include "Instance.h"
#include "Surface.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "Swapchain.h"
#include "Queue.h"

// Maybe at some point make it so u can create however may queues u want

namespace Wuu::Vulkan {

    class Renderer {
    public:

        Renderer() : m_instance(InstanceCreateInfo()), m_physicalDevice(), m_swapchain() {}

        virtual bool render(GLFWwindow* window) = 0;

        [[nodiscard]] auto& getPhysicalDevice() noexcept { return m_physicalDevice; }
        [[nodiscard]] auto& getLogicalDevice() noexcept { return m_logicalDevice; }
        [[nodiscard]] auto& getSwapchain() noexcept { return m_swapchain; }
        [[nodiscard]] auto& getInstance() noexcept { return m_instance; }

        //prob change this at some point
        [[nodiscard]] auto& getGraphicsQueue() noexcept { return m_graphicsQueue; }

    protected:

        Instance m_instance;
        Surface m_surface;
        PhysicalDevice m_physicalDevice;
        LogicalDevice m_logicalDevice;
        Swapchain m_swapchain;

        Queue m_graphicsQueue;
        Queue m_presentQueue;

        void initializeRenderer(GLFWwindow* window);
    };

}


#endif //WUU_RENDERER_H
