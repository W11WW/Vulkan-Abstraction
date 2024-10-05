//
// Created by Michael Ferents on 13/03/2022.
//

#ifndef WUU_MEMORYFUNCTIONS_H
#define WUU_MEMORYFUNCTIONS_H

// TODO: 90% this wont work coz its included inside the depth image
#include "MemoryPool.h"
#include "MemoryCommandBuffer.h"
#include "Buffer.h"
#include "Third-Party/stb_image.h"
#include "Utils.h"

static void transitionImageLayout(LogicalDevice& logicalDevice, MemoryPool& memoryPool, vk::Image& image, vk::ImageLayout oldlayout, vk::ImageLayout newLayout)
{
    MemoryCommandBuffer commandBuffer {};

    commandBuffer.setBuffer(logicalDevice, memoryPool.getCommandPool(), vk::CommandBufferLevel::ePrimary);

    commandBuffer.beginCommandBufferRecord();

    vk::ImageMemoryBarrier barrier {};
    barrier.oldLayout = oldlayout;
    barrier.newLayout = newLayout;

    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    barrier.image = image;
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
    memoryPool.getQueue().getQueue().submit(submitInfo, {});
    memoryPool.getQueue().getQueue().waitIdle();

    commandBuffer.destroy(logicalDevice, memoryPool.getCommandPool());

}

static void createImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, uint32_t width, uint32_t height,
                        vk::Format format, vk::ImageTiling tiling, vk::Flags<vk::ImageUsageFlagBits> usage,
                        vk::MemoryPropertyFlagBits properties, vk::Image& image, vk::DeviceMemory& imageMemory)
{
    vk::ImageCreateInfo imageCreateInfo {};
    imageCreateInfo.imageType = vk::ImageType::e2D;
    imageCreateInfo.extent.width = width;
    imageCreateInfo.extent.height = height;
    imageCreateInfo.extent.depth = 1,
            imageCreateInfo.mipLevels = 1;
    imageCreateInfo.arrayLayers = 1;
    imageCreateInfo.format = format;
    imageCreateInfo.tiling = tiling;
    imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageCreateInfo.usage = usage;
    imageCreateInfo.samples = vk::SampleCountFlagBits::e1;
    imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;

    image = logicalDevice.getLogicalDevice().createImage(imageCreateInfo);

    vk::MemoryRequirements memoryRequirements{};
    logicalDevice.getLogicalDevice().getImageMemoryRequirements(image, &memoryRequirements);

    vk::MemoryAllocateInfo allocateInfo{};
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, properties);

    imageMemory = logicalDevice.getLogicalDevice().allocateMemory(allocateInfo);
    logicalDevice.getLogicalDevice().bindImageMemory(image, imageMemory, 0);
}

// Creates a buffer with a specific size but does not allocate data into it and only accepts one buffer with an offset of 0 inside the device memory
static void createBuffer(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, vk::DeviceSize size,
                         vk::Flags<vk::BufferUsageFlagBits> usage, vk::Flags<vk::MemoryPropertyFlagBits> properties,
                         vk::Buffer& buffer, vk::DeviceMemory& bufferMemory)
{
    buffer = logicalDevice.getLogicalDevice().createBuffer(vk::BufferCreateInfo(vk::BufferCreateFlags(), size, usage));

    auto memoryRequirements = logicalDevice.getLogicalDevice().getBufferMemoryRequirements(buffer);

    vk::MemoryAllocateInfo allocateInfo = {};
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, properties);

    bufferMemory = logicalDevice.getLogicalDevice().allocateMemory(allocateInfo);

    logicalDevice.getLogicalDevice().bindBufferMemory(buffer, bufferMemory, 0);
}

static void copyBufferToImage(LogicalDevice& logicalDevice, MemoryPool& memoryPool, vk::Buffer& buffer, vk::Image& image, uint32_t width, uint32_t height)
{
    MemoryCommandBuffer commandBuffer {};

    commandBuffer.setBuffer(logicalDevice, memoryPool.getCommandPool(), vk::CommandBufferLevel::ePrimary);

    commandBuffer.beginCommandBufferRecord();

    vk::BufferImageCopy bufferImageCopy {};
    bufferImageCopy.bufferOffset = 0;
    bufferImageCopy.bufferRowLength = 0;
    bufferImageCopy.bufferImageHeight = 0;
    bufferImageCopy.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    bufferImageCopy.imageSubresource.mipLevel = 0;
    bufferImageCopy.imageSubresource.baseArrayLayer = 0;
    bufferImageCopy.imageSubresource.layerCount = 1;
    bufferImageCopy.imageOffset = vk::Offset3D(0,0,0);
    bufferImageCopy.imageExtent = vk::Extent3D(width, height, 1);

    commandBuffer.recordCopyBufferToImage(buffer, image, vk::ImageLayout::eTransferDstOptimal, bufferImageCopy);

    commandBuffer.endCommandBufferRecord();

    vk::SubmitInfo submitInfo {};
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer.getCommandBuffer();

    // TODO: like above this is stupid get get
    memoryPool.getQueue().getQueue().submit(submitInfo, {});
    memoryPool.getQueue().getQueue().waitIdle();

    commandBuffer.destroy(logicalDevice, memoryPool.getCommandPool());
}

static void createDescriptorImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool,
                                  vk::Image& image, vk::DeviceMemory& deviceMemory, std::string iamgeName)
{

    int imgWidth, imgHeight, imgChannels;
    std::string path = "../Graphics/Texture/" + iamgeName;
    stbi_uc* pixels = stbi_load(path.c_str(), &imgWidth, &imgHeight, &imgChannels, STBI_rgb_alpha);

    vk::DeviceSize imageSize = imgWidth * imgHeight * 4;

    if(!pixels) return;

    Buffer stagingBuffer;

    createBuffer(logicalDevice, physicalDevice, imageSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                 stagingBuffer.getBuffer(), stagingBuffer.getDeviceMemory());

    void* data;
    logicalDevice.getLogicalDevice().mapMemory(stagingBuffer.getDeviceMemory(), 0, imageSize, vk::MemoryMapFlags(), &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    logicalDevice.getLogicalDevice().unmapMemory(stagingBuffer.getDeviceMemory());
    stbi_image_free(pixels);

    createImage(logicalDevice, physicalDevice, imgWidth, imgHeight, vk::Format::eR8G8B8A8Srgb, vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled,
                vk::MemoryPropertyFlagBits::eDeviceLocal, image, deviceMemory);

    transitionImageLayout(logicalDevice, memoryPool, image, vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal);
    copyBufferToImage(logicalDevice, memoryPool, stagingBuffer.getBuffer(), image, static_cast<uint32_t>(imgWidth), static_cast<uint32_t>(imgHeight));
    transitionImageLayout(logicalDevice, memoryPool, image, vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal);
}

static void copyBuffer(LogicalDevice& logicalDevice, vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size, MemoryPool& memoryPool)
{
    MemoryCommandBuffer commandBuffer {};

    commandBuffer.setBuffer(logicalDevice, memoryPool.getCommandPool(), vk::CommandBufferLevel::ePrimary);

    commandBuffer.beginCommandBufferRecord();

    commandBuffer.recordCopyBuffer(srcBuffer, dstBuffer, vk::BufferCopy(0, 0, size));

    commandBuffer.endCommandBufferRecord();

    vk::SubmitInfo submitInfo {};
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer.getCommandBuffer();

    // TODO: like above this is stupid get get
    memoryPool.getQueue().getQueue().submit(submitInfo, {});
    memoryPool.getQueue().getQueue().waitIdle();

    commandBuffer.destroy(logicalDevice, memoryPool.getCommandPool());
}

template<typename T>
static void createVertexBuffer(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, const vk::DeviceSize size,
                               vk::Buffer& buffer, vk::DeviceMemory& deviceMemory, std::vector<T>& vertices,
                               MemoryPool& memoryPool)
{
    Buffer stagingBuffer;

    createBuffer(logicalDevice, physicalDevice, size, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                 stagingBuffer.getBuffer(), stagingBuffer.getDeviceMemory());

    void* dataPtr = nullptr;
    logicalDevice.getLogicalDevice().mapMemory(stagingBuffer.getDeviceMemory(), 0, sizeof(vertices[0]) * vertices.size(), vk::MemoryMapFlags(), &dataPtr);
    memcpy(dataPtr, vertices.data(), static_cast<size_t>(sizeof(vertices[0]) * vertices.size()));
    logicalDevice.getLogicalDevice().unmapMemory(stagingBuffer.getDeviceMemory());

    createBuffer(logicalDevice, physicalDevice, size, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal,
                 buffer, deviceMemory);

    copyBuffer(logicalDevice, stagingBuffer.getBuffer(), buffer, size, memoryPool);
}

template<typename T>
static void createIndexBuffer(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, const vk::DeviceSize size,
                              vk::Buffer& buffer, vk::DeviceMemory& bufferMemory, std::vector<T>& indices,
                              MemoryPool& memoryPool)
{
    Buffer stagingBuffer;

    createBuffer(logicalDevice, physicalDevice, size, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                 stagingBuffer.getBuffer(), stagingBuffer.getDeviceMemory());

    void* dataPtr = nullptr;
    logicalDevice.getLogicalDevice().mapMemory(stagingBuffer.getDeviceMemory(), 0, sizeof(indices[0]) * indices.size(), vk::MemoryMapFlags(), &dataPtr);
    memcpy(dataPtr, indices.data(), static_cast<size_t>(sizeof(indices[0]) * indices.size()));
    logicalDevice.getLogicalDevice().unmapMemory(stagingBuffer.getDeviceMemory());

    createBuffer(logicalDevice, physicalDevice, size, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal,
                 buffer, bufferMemory);

    copyBuffer(logicalDevice, stagingBuffer.getBuffer(), buffer, size, memoryPool);
}

#endif //WUU_MEMORYFUNCTIONS_H
