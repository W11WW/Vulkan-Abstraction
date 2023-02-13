//
// Created by Michael Ferents on 29/01/2023.
//

#include "Context.h"
using namespace Wuu::UI;

void Context::update_input()
{

}

void Context::reset_input()
{
    m_windowHandle.m_callbackInfo.reset();
}

void Context::render(GLFWwindow* window)
{
    m_vulkanHandle.render(window);
}

void Context::Button()
{

}

void Context::Image()
{

}

void Context::Text()
{

}
