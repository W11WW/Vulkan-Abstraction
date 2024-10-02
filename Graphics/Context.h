//
// Created by Michael Ferents on 29/01/2023.
//

#ifndef WUU_CONTEXT_H
#define WUU_CONTEXT_H
#include "VulkanHandle.h"
#include "WindowHandle.h"

class Context {
public:

    void update_input();
    void reset_input();

    void render(GLFWwindow* window);

    auto getVulkanHandle() -> VulkanHandle& { return m_vulkanHandle; }
    auto getWindowHandle() -> WindowHandle& { return m_windowHandle; }

    auto getVulkanHandlePointer() -> VulkanHandle* { return &m_vulkanHandle; }
    auto getWindowHandlePointer() -> WindowHandle* { return &m_windowHandle; }

private:

    VulkanHandle m_vulkanHandle;
    WindowHandle m_windowHandle;

};

#endif //WUU_CONTEXT_H
