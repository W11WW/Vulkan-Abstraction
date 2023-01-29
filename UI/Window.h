//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_WINDOW_H
#define WUU_WINDOW_H
#include <iostream>
#include <GLFW/glfw3.h>

#include "VulkanHandle.h"
#include "WindowHandle.h"
#include "UIHandle.h"

namespace Wuu {

    class Window {
    public:

        Window() = default;

        void initialize();
        void run();
        void destroy();

    private:

        GLFWwindow* m_window;

        VulkanHandle m_vulkanHandle;
        WindowHandle m_windowHandle;
        UIHandle m_uiHandle;

    };

}


#endif //WUU_WINDOW_H
