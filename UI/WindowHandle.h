//
// Created by Michael Ferents on 08/04/2022.
//

#ifndef WUU_WINDOWHANDLE_H
#define WUU_WINDOWHANDLE_H
#include <GLFW/glfw3.h>
#include "WindowUtils.h"

namespace Wuu::UI {

    class WindowHandle {
    public:

        WindowCallbackInfo m_callbackInfo {};

        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    };

}

#endif //WUU_WINDOWHANDLE_H
