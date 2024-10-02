//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_VERTEXTYPES_H
#define WUU_VERTEXTYPES_H

#include <vulkan/vulkan.hpp>
#include "Third-Party/glm/glm.hpp"

struct Vertex {

    glm::vec3 pos;
    glm::vec2 texCoords;

    static vk::VertexInputBindingDescription getBindingDescription()
    {
        vk::VertexInputBindingDescription bindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);
        return bindingDescription;
    }

    static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions()
    {
        std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions = {

                vk::VertexInputAttributeDescription(0,0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
                vk::VertexInputAttributeDescription(1,0, vk::Format::eR32G32Sfloat, offsetof(Vertex, texCoords))

        };

        return attributeDescriptions;
    }
};

#endif //WUU_VERTEXTYPES_H
