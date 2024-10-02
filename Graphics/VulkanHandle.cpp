//
// Created by Michael Ferents on 05/04/2022.
//

#include "VulkanHandle.h"

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

    std::vector<DescriptorType> types { m_uniformBuffer, m_images[0] };

    ShaderModule vertShader;
    vertShader.setEntryPointName("main");
    vertShader.setShaderPath("../Graphics/Shader/vert.spv");
    vertShader.setShaderStage(vk::ShaderStageFlagBits::eVertex);
    vertShader.initialize(m_renderer.getLogicalDevice());

    ShaderModule fragShader;
    fragShader.setEntryPointName("main");
    fragShader.setShaderPath("../Graphics/Shader/frag.spv");
    fragShader.setShaderStage(vk::ShaderStageFlagBits::eFragment);
    fragShader.initialize(m_renderer.getLogicalDevice());

    m_pipeline.addModule(vertShader);
    m_pipeline.addModule(fragShader);

    m_pipeline.initialize<Vertex, PushConstantData>(window, m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage, types, m_renderPass);

    m_descriptorSetUniformBuffer.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[0]);
    m_descriptorSetUniformBuffer.write(m_renderer.getLogicalDevice(), m_uniformBuffer);

    m_imageSet.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[1]);
    m_imageSet.write(m_renderer.getLogicalDevice(), m_images);

    m_square.setShape(m_renderer.getLogicalDevice(), m_renderer.getPhysicalDevice(), m_memoryPool, "al");
}

// what im doing here rn is retarded but im testing stuff which also doesnt seem to work great : )

void VulkanHandle::updateCommandBuffers()
{
    std::vector<DescriptorSet> sets = { m_descriptorSetUniformBuffer, m_imageSet };
    m_renderer.getCommandBuffers().resize(2);

    for(auto& buffer : m_renderer.getCommandBuffers())
    {
        for(int i = 0; i < 2; i++)
        {
            buffer[i].setBuffer(m_renderer.getLogicalDevice(), m_renderer.getCommandPool(), vk::CommandBufferLevel::ePrimary);
        }
    }

    for(int i = 0; i < m_renderer.getSwapchain().getSize(); i++)
    {
        m_renderer.getCommandBuffers()[0][i].beginCommandBufferRecord();
        m_renderer.getCommandBuffers()[0][i].bindRenderPass(m_renderPass, m_renderer.getSwapchain(), i);
        m_renderer.getCommandBuffers()[0][i].bindPipeline(m_pipeline);
        m_renderer.getCommandBuffers()[0][i].bindShape(m_square);
        m_renderer.getCommandBuffers()[0][i].bindDescriptorSets(m_pipeline, sets);

        glm::vec3 pos1(1.0f, 1.0f, 1.0f);
        m_renderer.getCommandBuffers()[0][i].drawIndexed(m_pipeline, m_square, pos1);

        glm::vec3 pos2(1.0f, 3.0f, 1.0f);
        m_renderer.getCommandBuffers()[0][i].drawIndexed(m_pipeline, m_square, pos2);

        glm::vec3 pos3(3.0f, 1.0f, 1.0f);
        m_renderer.getCommandBuffers()[0][i].drawIndexed(m_pipeline, m_square, pos3);

        m_renderer.getCommandBuffers()[0][i].unbindRenderPass();

        m_renderer.getCommandBuffers()[0][i].endCommandBufferRecord();
    }

    for(int i = 0; i < m_renderer.getSwapchain().getSize(); i++)
    {
        m_renderer.getCommandBuffers()[1][i].beginCommandBufferRecord();
        m_renderer.getCommandBuffers()[1][i].bindRenderPass(m_renderPass, m_renderer.getSwapchain(), i);
        m_renderer.getCommandBuffers()[1][i].bindPipeline(m_pipeline);
        m_renderer.getCommandBuffers()[1][i].bindShape(m_square);
        m_renderer.getCommandBuffers()[1][i].bindDescriptorSets(m_pipeline, sets);

        glm::vec3 pos1(1.5f, 1.5f, 1.0f);
        m_renderer.getCommandBuffers()[1][i].drawIndexed(m_pipeline, m_square, pos1);

        glm::vec3 pos2(1.0f, 3.0f, 2.0f);
        m_renderer.getCommandBuffers()[1][i].drawIndexed(m_pipeline, m_square, pos2);

        glm::vec3 pos3(3.0f, 1.0f, 4.0f);
        m_renderer.getCommandBuffers()[1][i].drawIndexed(m_pipeline, m_square, pos3);

        m_renderer.getCommandBuffers()[1][i].unbindRenderPass();

        m_renderer.getCommandBuffers()[1][i].endCommandBufferRecord();
    }
}

// TODO: seems like we destroy the image buffer every time we resize the window which would coz a lot of waste in memory and performance

void VulkanHandle::render(GLFWwindow* window)
{
    m_uniformBuffer.updateUniformBuffer(m_renderer.getLogicalDevice(), m_renderer.getPhysicalDevice(), m_renderer.getSwapchain());

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

        std::vector<DescriptorType> types { m_uniformBuffer, m_images[0] };
        m_pipeline.destroy(m_renderer.getLogicalDevice());
        m_pipeline.initialize<Vertex, PushConstantData>(window, m_renderer.getLogicalDevice(), m_renderer.getSwapchain(), m_depthImage, types, m_renderPass);


        m_descriptorSetUniformBuffer.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[0]);
        m_descriptorSetUniformBuffer.write(m_renderer.getLogicalDevice(), m_uniformBuffer);

        m_imageSet.initialize(m_renderer.getLogicalDevice(), m_descriptorPool, m_pipeline.getDescriptorSetLayout()[1]);
        m_imageSet.write(m_renderer.getLogicalDevice(), m_images);
    }
}

void VulkanHandle::destroy()
{

}