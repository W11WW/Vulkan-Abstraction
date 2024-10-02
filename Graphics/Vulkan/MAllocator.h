//
// Created by Michael Ferents on 01/08/2023.
//

#ifndef WUU_MALLOCATOR_H
#define WUU_MALLOCATOR_H

#include "MemoryPool.h"
#include "Logger.h"
#include "MemoryCommandBuffer.h"
#include "Buffer.h"
#include "Image.h"
#include "Third-Party/stb_image.h"

struct Event {

    explicit Event(std::string_view message) : event(message) {}

    std::string event;

    [[nodiscard]] std::string_view to_string() const
    {
        return event;
    }
};

struct State {

    explicit State(std::string_view message) : state(message) {}

    std::string state;

    [[nodiscard]] std::string_view to_string() const
    {
        return state;
    }
};

struct BufferCreateInfo
{
public:

    vk::DeviceSize m_size;
    vk::Flags<vk::BufferUsageFlagBits> m_usage;
    vk::Flags<vk::MemoryPropertyFlagBits> m_properties;

};

struct ImageCreateInfo
{
public:

    uint32_t m_width;
    uint32_t m_height;

    vk::ImageCreateInfo m_info;
    vk::MemoryPropertyFlagBits m_properties;
};

// Create a system with Command Pools such that you can control when and what commands to do
// for the moment we do it one at a time - but also often when creating these command buffers
// are specific to a buffer or image and so maybe its now worth or possible to try this
class MAllocator {
public:

    MAllocator() = default;

    // Creates a buffer with a specific size but does not allocate data into it and only accepts one buffer with an offset of 0 inside the device memory
    auto createBuffer(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, BufferCreateInfo info)
    {
        std::unique_ptr<Buffer> buffer {};
        buffer->getBuffer() = logicalDevice.getLogicalDevice().createBuffer(vk::BufferCreateInfo(vk::BufferCreateFlags(), info.m_size, info.m_usage));


        auto memoryRequirements = logicalDevice.getLogicalDevice().getBufferMemoryRequirements(buffer->getBuffer());

        vk::MemoryAllocateInfo allocateInfo = {};
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, info.m_properties);

        buffer->getDeviceMemory() = logicalDevice.getLogicalDevice().allocateMemory(allocateInfo);

        logicalDevice.getLogicalDevice().bindBufferMemory(buffer->getBuffer(), buffer->getDeviceMemory(), 0);

        return buffer;
    }

    auto createImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, ImageCreateInfo info)
    {
        std::unique_ptr<Image> image {};
        image->getImage() = logicalDevice.getLogicalDevice().createImage(info.m_info);

        vk::MemoryRequirements memoryRequirements{};
        logicalDevice.getLogicalDevice().getImageMemoryRequirements(image->getImage(), &memoryRequirements);

        vk::MemoryAllocateInfo allocateInfo{};
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, info.m_properties);

        image->getDeviceMemory() = logicalDevice.getLogicalDevice().allocateMemory(allocateInfo);
        logicalDevice.getLogicalDevice().bindImageMemory(image->getImage(), image->getDeviceMemory(), 0);

        return image;
    }

    void transitionImageLayout(LogicalDevice& logicalDevice, std::unique_ptr<Image>& image, vk::ImageLayout oldlayout, vk::ImageLayout newLayout)
    {
        MemoryCommandBuffer commandBuffer {};

        commandBuffer.setBuffer(logicalDevice, m_memoryPool.getCommandPool(), vk::CommandBufferLevel::ePrimary);

        commandBuffer.beginCommandBufferRecord();

        vk::ImageMemoryBarrier barrier {};
        barrier.oldLayout = oldlayout;
        barrier.newLayout = newLayout;

        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

        barrier.image = image->getImage();
        barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;

        if(newLayout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
        {
            barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
        } else {
            barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        }

        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        vk::PipelineStageFlags sourceStage;
        vk::PipelineStageFlags destinationStage;

        if(oldlayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal)
        {
            barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

            sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
            destinationStage = vk::PipelineStageFlagBits::eTransfer;
        } else if (oldlayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal)
        {
            barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
            barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

            sourceStage = vk::PipelineStageFlagBits::eTransfer;
            destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
        } else if (oldlayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eDepthStencilAttachmentOptimal)
        {
            barrier.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite;

            sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;
            destinationStage = vk::PipelineStageFlagBits::eEarlyFragmentTests;
        } else {
            throw std::invalid_argument("Unsupported layout transition!");
        }

        commandBuffer.recordPipelineBarrier(sourceStage, destinationStage, barrier);

        commandBuffer.endCommandBufferRecord();

        vk::SubmitInfo submitInfo {};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer.getCommandBuffer();

        // TODO: this get get is stupid
        m_memoryPool.getQueue().getQueue().submit(submitInfo, {});
        m_memoryPool.getQueue().getQueue().waitIdle();

        commandBuffer.destroy(logicalDevice, m_memoryPool.getCommandPool());
    }



protected:

    MemoryPool m_memoryPool;

    Logger<Event> m_eventLogger {};
    Logger<State> m_stateLogger {};
};


#endif //WUU_MALLOCATOR_H
