//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_MESH_H
#define WUU_MESH_H

#include "Third-Party/tiny_obj_loader.h"

#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "IndexBuffer.h"
#include "MemoryFunctions.h"

class Mesh {
public:

    Mesh() = default;

    virtual void setShape(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, std::string filePath);

    [[nodiscard]] auto& getVertexBuffer() noexcept { return m_vertexBuffer; }
    [[nodiscard]] auto& getIndexBuffer() noexcept { return m_indicesBuffer; }

protected:

    VertexBuffer m_vertexBuffer {};
    IndexBuffer m_indicesBuffer {};

};

#endif //WUU_MESH_H
