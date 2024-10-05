//
// Created by Michael Ferents on 05/04/2022.
//

#ifndef WUU_VULKANHANDLE_H
#define WUU_VULKANHANDLE_H
#include <iostream>
#include <GLFW/glfw3.h>

#include "Vulkan/BasicRenderer.h"
#include "Vulkan/MemoryPool.h"
#include "Vulkan/DepthImage.h"
#include "Vulkan/DescriptorUniformBuffer.h"
#include "Vulkan/UniformBufferType.h"
#include "Vulkan/DescriptorSetUniformBuffer.h"
#include "Vulkan/DescriptorPool.h"
#include "Vulkan/Pipeline.h"
#include "Vulkan/Mesh.h"
#include "Vulkan/DescriptorImage.h"
#include "Vulkan/DescriptorSetImage.h"
#include "Vulkan/MemoryFunctions.h"
#include "Vulkan/MAllocator.h"

class VulkanHandle {
public:

    VulkanHandle() = default;

    void initialize(GLFWwindow* window);

    void render(GLFWwindow* window);

    void updateCommandBuffers();

    void destroy();

private:

    BasicRenderer m_renderer;
    MemoryPool m_memoryPool;
    DepthImage m_depthImage;
    DescriptorUniformBuffer<UniformBufferObject> m_uniformBuffer;
    DescriptorPool m_descriptorPool;
    DescriptorSetUniformBuffer m_descriptorSetUniformBuffer;
    RenderPass m_renderPass;
    Pipeline m_pipeline;
    MAllocator m_allocator;

    Mesh m_square {};
    std::vector<DescriptorImage> m_images {};
    DescriptorSetImage m_imageSet {};

};


#endif //WUU_VULKANHANDLE_H
