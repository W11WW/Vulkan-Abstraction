//
// Created by Michael Ferents on 21/03/2022.
//

#include "Window.h"

using namespace Wuu;

void Window::initialize()
{
    if(glfwInit())
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        //glfwWindowHint(GLFW_RESIZABLE, true);
    }

    m_window = glfwCreateWindow(1280, 720, "Wuu", nullptr, nullptr);
    if(!m_window) { glfwTerminate(); }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_windowHandle);

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
    m_vulkanHandle.initialize(m_window);
}

void Window::run()
{
    m_vulkanHandle.updateCommandBuffers();

    while(!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        // check input buffer

        m_windowHandle.m_callbackInfo.reset();

        m_vulkanHandle.render(m_window);
    }
}

void Window::destroy()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();

    m_vulkanHandle.destroy();
}