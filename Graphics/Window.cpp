//
// Created by Michael Ferents on 21/03/2022.
//

#include "Window.h"

void Window::initialize()
{
    if(glfwInit())
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        //glfwWindowHint(GLFW_RESIZABLE, true);
    }

    m_window = glfwCreateWindow(1280, 720, "Vulkan-Abstraction", nullptr, nullptr);
    if(!m_window) { glfwTerminate(); }

    glfwMakeContextCurrent(m_window);
}

auto Window::is_running() -> bool
{
    return !glfwWindowShouldClose(m_window);
}

void Window::poll_events()
{
    glfwPollEvents();
}

auto Window::create_context() -> std::unique_ptr<Context>
{

    std::unique_ptr<Context> ctx(new Context);

    glfwSetWindowUserPointer(m_window, ctx->getWindowHandlePointer());

    auto mFunc = [](GLFWwindow* window, double xpos, double ypos)
    {
        static_cast<WindowHandle*>(glfwGetWindowUserPointer(window))->mouse_callback(window, xpos, ypos);
    };
    glfwSetCursorPosCallback(m_window, mFunc);
    auto sFunc = [](GLFWwindow* window, double xoffset, double yoffset)
    {
        static_cast<WindowHandle*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window, sFunc);
    auto kFunc = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<WindowHandle*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, kFunc);
    auto mbFunc = [](GLFWwindow* window, int button, int action, int mods)
    {
        static_cast<WindowHandle*>(glfwGetWindowUserPointer(window))->mouse_button_callback(window, button, action, mods);
    };
    glfwSetMouseButtonCallback(m_window, mbFunc);

    ctx->getVulkanHandle().initialize(m_window);
    ctx->getVulkanHandle().updateCommandBuffers();

    return ctx;
}

void Window::destroy()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}