//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_SHAPE_H
#define WUU_SHAPE_H

#include "UI/Vulkan/Third-Party/tiny_obj_loader.h"

#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "IndexBuffer.h"
#include "MemoryFunctions.h"

namespace Wuu::Vulkan {

    class Shape {
    public:

        Shape() = default;

        virtual void setShape(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, std::string filePath);

        [[nodiscard]] auto& getVertexBuffer() noexcept { return m_vertexBuffer; }
        [[nodiscard]] auto& getIndexBuffer() noexcept { return m_indicesBuffer; }

    protected:

        VertexBuffer m_vertexBuffer {};
        IndexBuffer m_indicesBuffer {};

    };

}

#endif //WUU_SHAPE_H
