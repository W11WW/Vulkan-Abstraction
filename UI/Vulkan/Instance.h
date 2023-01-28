//
// Created by Michael Ferents on 10/03/2022.
//

#ifndef WUU_INSTANCE_H
#define WUU_INSTANCE_H
#include <utility>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include <iostream>

namespace Wuu::Vulkan {

    class Instance {
    public:

        explicit Instance(const InstanceCreateInfo&&  info) : m_info(info) {}

        virtual void initializeInstance();
        virtual void destroy();

        [[nodiscard]] auto& getInfo() noexcept { return m_info; }
        [[nodiscard]] auto& getInstance() noexcept { return m_instance; }

    protected:

        InstanceCreateInfo m_info;
        vk::Instance m_instance;
        vk::DebugUtilsMessengerEXT m_debugUtilsMessengerEXT;

    };


}

#endif //WUU_INSTANCE_H
