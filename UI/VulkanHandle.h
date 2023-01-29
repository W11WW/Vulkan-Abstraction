//
// Created by Michael Ferents on 05/04/2022.
//

#ifndef WUU_VULKANHANDLE_H
#define WUU_VULKANHANDLE_H
#include <iostream>
#include <GLFW/glfw3.h>

#include "UI/Vulkan/UIRenderer.h"
#include "UI/Vulkan/MemoryPool.h"
#include "UI/Vulkan/DepthImage.h"
#include "UI/Vulkan/DescriptorUniformBuffer.h"
#include "UI/Vulkan/UniformBufferType.h"
#include "UI/Vulkan/DescriptorSetUniformBuffer.h"
#include "UI/Vulkan/DescriptorPool.h"
#include "UI/Vulkan/Shader.h"
#include "UI/Vulkan/Shape.h"
#include "UI/Vulkan/DescriptorImage.h"
#include "UI/Vulkan/DescriptorSetImage.h"
#include "UI/Vulkan/MemoryFunctions.h"
#include "Core/Data.h"

namespace Wuu {

    class VulkanHandle {
    public:

        VulkanHandle() = default;

        void initialize(GLFWwindow* window);

        void render(GLFWwindow* window);

        void updateCommandBuffers();
        void updateBuffers();
        void updateImages();

        void destroy();

    private:

        Vulkan::UIRenderer m_renderer;
        Vulkan::MemoryPool m_memoryPool;
        Vulkan::DepthImage m_depthImage;
        Vulkan::DescriptorUniformBuffer<UniformBufferObject> m_uniformBuffer;
        Vulkan::DescriptorPool m_descriptorPool;
        Vulkan::DescriptorSetUniformBuffer m_descriptorSetUniformBuffer;
        Vulkan::Shader<Vertex> m_shader;

        Vulkan::Shape m_square {};
        std::vector<Vulkan::DescriptorImage> m_images {};
        Vulkan::DescriptorSetImage m_imageSet {};

        Element test {};
        Element test2 {};

    };

}


#endif //WUU_VULKANHANDLE_H
