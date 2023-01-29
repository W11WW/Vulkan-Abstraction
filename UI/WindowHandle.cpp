//
// Created by Michael Ferents on 08/04/2022.
//

#include "WindowHandle.h"

using namespace Wuu;

void WindowHandle::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    m_callbackInfo.mouseXpos = xpos;
    m_callbackInfo.mouseYpos = ypos;

    std::cout << "Mouse Position: " << xpos << " " << ypos << std::endl;
}

void WindowHandle::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    m_callbackInfo.keyboardKeyAction = action;
    m_callbackInfo.keyboardKeyPressed = key;
}

void WindowHandle::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    m_callbackInfo.mouseButtonPressed = button;
    m_callbackInfo.mouseButtonAction = action;
}

void WindowHandle::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    m_callbackInfo.mouseScrollXoffset = xoffset;
    m_callbackInfo.mouseScrollYoffset = yoffset;
}