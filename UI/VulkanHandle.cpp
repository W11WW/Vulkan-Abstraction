//
// Created by Michael Ferents on 05/04/2022.
//

#include "VulkanHandle.h"

using namespace Wuu;

void VulkanHandle::initialize(GLFWwindow* window)
{
    m_renderer.initialize(window);
    m_memoryPool.initialize(m_renderer.getLogicalDevice(),
                            m_renderer.getPhysicalDevice(),
                            m_renderer.getLogicalDevice().getTransferQueueIndex());

    m_depthImage.setImage(m_renderer.getLogicalDevice(),
                          m_renderer.getPhysicalDevice(),
                          m_memoryPool,
                          m_renderer.getSwapchain().getExtent());

    m_renderPass.initialize(m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage);

    m_descriptorPool.setPool(m_renderer.getLogicalDevice(), 1, 1, 2);

    m_uniformBuffer.initialize(m_renderer.getLogicalDevice(),
                               m_renderer.getPhysicalDevice());

    m_uniformBuffer.setBinding(0);
    m_uniformBuffer.setType(vk::DescriptorType::eUniformBuffer);
    m_uniformBuffer.setShaderStage(vk::ShaderStageFlagBits::eVertex);

    m_images.resize(1);
    m_images[0].setBinding(1);
    m_images[0].setType(vk::DescriptorType::eCombinedImageSampler);
    m_images[0].setShaderStage(vk::ShaderStageFlagBits::eFragment);
    m_images[0].setImage(m_renderer.getLogicalDevice(), m_renderer.getPhysicalDevice(), m_memoryPool, "viking_room.png");

    std::vector<Vulkan::DescriptorType> types { m_uniformBuffer, m_images[0] };
    m_pipeline.setPath("../UI/Shaders/vert.spv", "../UI/Shaders/frag.spv");
    m_pipeline.initialize<Vertex>(window, m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage, types, m_renderPass);

    m_descriptorSetUniformBuffer.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[0]);
    m_descriptorSetUniformBuffer.write(m_renderer.getLogicalDevice(), m_uniformBuffer);

    m_imageSet.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[1]);
    m_imageSet.write(m_renderer.getLogicalDevice(), m_images);

    m_square.setShape(m_renderer.getLogicalDevice(), m_renderer.getPhysicalDevice(), m_memoryPool, "al");

    test.setPosition(glm::vec3(1, 1, 1));
    test2.setPosition(glm::vec3(1, 1.5, 1));
}

void VulkanHandle::updateCommandBuffers()
{
    std::vector<vk::DescriptorSet> sets = { m_descriptorSetUniformBuffer.getDescriptorSet(), m_imageSet.getDescriptorSet() };

    for(int i = 0; i < m_renderer.getSwapchain().getSize(); i++)
    {
        m_renderer.getCommandBuffers()[i].beginCommandBufferRecord();
        m_renderer.getCommandBuffers()[i].recordElement(m_pipeline, m_renderPass, test, sets, m_square, i, m_renderer.getSwapchain());
        m_renderer.getCommandBuffers()[i].recordElement(m_pipeline, m_renderPass, test2, sets, m_square, i, m_renderer.getSwapchain());
        m_renderer.getCommandBuffers()[i].endCommandBufferRecord();
    }
}

void VulkanHandle::updateBuffers()
{

}

void VulkanHandle::updateImages()
{

}

// TODO: seems like we destroy the image buffer every time we resize the window which would coz a lot of waste in memory and performance

void VulkanHandle::render(GLFWwindow* window)
{

    m_uniformBuffer.updateUniformBuffer(m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), test);

    if(!m_renderer.render(window))
    {
        m_depthImage.destroy(m_renderer.getLogicalDevice());
        m_depthImage.setImage(m_renderer.getLogicalDevice(),
                              m_renderer.getPhysicalDevice(),
                              m_memoryPool,
                              m_renderer.getSwapchain().getExtent());

        m_renderPass.destroy(m_renderer.getLogicalDevice());
        m_renderPass.initialize(m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage);

        m_descriptorPool.destroy(m_renderer.getLogicalDevice());
        m_descriptorPool.setPool(m_renderer.getLogicalDevice(), 1, 1, 2);

        m_uniformBuffer.destroy(m_renderer.getLogicalDevice());
        m_uniformBuffer.initialize(m_renderer.getLogicalDevice(),
                                   m_renderer.getPhysicalDevice());

        m_images[0].destroy(m_renderer.getLogicalDevice());
        m_images[0].setImage(m_renderer.getLogicalDevice(), m_renderer.getPhysicalDevice(), m_memoryPool, "test.jpeg");

        std::vector<Vulkan::DescriptorType> types { m_uniformBuffer, m_images[0] };
        m_pipeline.destroy(m_renderer.getLogicalDevice());
        m_pipeline.initialize<Vertex>(window, m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage, types, m_renderPass);


        m_descriptorSetUniformBuffer.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[0]);
        m_descriptorSetUniformBuffer.write(m_renderer.getLogicalDevice(), m_uniformBuffer);

        m_imageSet.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[1]);
        m_imageSet.write(m_renderer.getLogicalDevice(), m_images);
    }
}

void VulkanHandle::destroy()
{

}