//
// Created by Michael Ferents on 21/03/2022.
//

#include "Shape.h"

using namespace Wuu::Vulkan;

void Shape::setShape(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, std::string filePath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "../UI/Shapes/al.obj" )) {
        throw std::runtime_error(warn + err);
    }

    std::vector<Vertex> vertices {};
    std::vector<uint32_t> indices {};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoords = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };



            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    m_vertexBuffer.getVerticesSize() = vertices.size();
    m_indicesBuffer.getIndicesSize() = indices.size();

    createVertexBuffer(logicalDevice, physicalDevice, sizeof(vertices[0]) * vertices.size(), m_vertexBuffer.getBuffer(), m_vertexBuffer.getDeviceMemory(),
                       vertices, memoryPool);
    createIndexBuffer(logicalDevice, physicalDevice, sizeof(indices[0]) * indices.size(), m_indicesBuffer.getBuffer(), m_indicesBuffer.getDeviceMemory(),
                      indices, memoryPool);
}