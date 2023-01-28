//
// Created by Michael Ferents on 12/03/2022.
//

#include "Renderer.h"

using namespace Wuu::Vulkan;

void Renderer::initializeRenderer(GLFWwindow *window)
{
    m_instance.initializeInstance();
    m_surface.initializeSurface(m_instance, window);
    m_physicalDevice.enumeratePhysicalDevices(m_instance);
    m_logicalDevice.initializeLogicalDevice(m_surface, m_physicalDevice);
    m_swapchain.initializeSwapchain(window, m_logicalDevice, m_physicalDevice, m_surface);

    m_graphicsQueue.setQueue(m_logicalDevice, m_logicalDevice.getGraphicsQueueIndex());
    m_presentQueue.setQueue(m_logicalDevice, m_logicalDevice.getPresentQueueIndex());
}