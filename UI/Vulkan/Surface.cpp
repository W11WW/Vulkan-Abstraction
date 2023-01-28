//
// Created by Michael Ferents on 11/03/2022.
//

#include "Surface.h"
using namespace Wuu::Vulkan;

void Surface::initializeSurface(Instance &instance, GLFWwindow *window)
{
    VkSurfaceKHR surfaceTmp {};
    glfwCreateWindowSurface(instance.getInstance(), window, nullptr, &surfaceTmp);
    m_surface = vk::SurfaceKHR(surfaceTmp);
}

void Surface::destroy(Instance &instance)
{
    instance.getInstance().destroySurfaceKHR(m_surface);
}