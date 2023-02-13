//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_WINDOW_H
#define WUU_WINDOW_H
#include <iostream>
#include <GLFW/glfw3.h>

#include "VulkanHandle.h"
#include "WindowHandle.h"
#include "Context.h"

namespace Wuu::UI {

    class Window {
    public:

        Window() = default;

        void initialize();
        void destroy();

        auto create_context() -> std::unique_ptr<Context>;
        auto is_running() -> bool;
        void poll_events();

        auto getGLFWWindow() -> GLFWwindow* { return m_window; }

    private:

        GLFWwindow* m_window;

    };

}


#endif //WUU_WINDOW_H
