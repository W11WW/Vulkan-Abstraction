//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_DESCRIPTORFUNCTIONS_H
#define WUU_DESCRIPTORFUNCTIONS_H
#include "UniformBufferType.h"
#include "UI/Element.h"
#include "Swapchain.h"

namespace Wuu::Vulkan {

    static inline void createUniformBufferObject(UniformBufferObject& ubo, Element& element, Swapchain& swapchain) noexcept
    {
        ubo.model = glm::mat4(1.0f);
        ubo.model = glm::translate(ubo.model, element.getPosition());
        ubo.model = glm::scale(ubo.model, glm::vec3 (0.7f, 0.7f, 0.7f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), (float) swapchain.getExtent().width / (float) swapchain.getExtent().height, 0.1f, 20.0f);
        ubo.proj[1][1] *= -1;
    }

}

#endif //WUU_DESCRIPTORFUNCTIONS_H
