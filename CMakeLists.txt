cmake_minimum_required(VERSION 3.20)
project(Vulkan-Abstraction)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

if(APPLE)
    add_executable(Vulkan-Abstraction main.cpp Graphics/Vulkan/Instance.cpp Graphics/Vulkan/Instance.h Graphics/Vulkan/Surface.cpp Graphics/Vulkan/Surface.h Graphics/Vulkan/PhysicalDevice.cpp Graphics/Vulkan/PhysicalDevice.h Graphics/Vulkan/LogicalDevice.cpp Graphics/Vulkan/LogicalDevice.h Graphics/Vulkan/Queue.cpp Graphics/Vulkan/Queue.h Graphics/Vulkan/Swapchain.cpp Graphics/Vulkan/Swapchain.h Graphics/Vulkan/Image.cpp Graphics/Vulkan/Image.h Graphics/Vulkan/CommandPool.cpp Graphics/Vulkan/CommandPool.h Graphics/Vulkan/CommandBuffer.cpp Graphics/Vulkan/CommandBuffer.h Graphics/Vulkan/Renderer.cpp Graphics/Vulkan/Renderer.h Graphics/Vulkan/MemoryPool.cpp Graphics/Vulkan/MemoryPool.h Graphics/Vulkan/MemoryFunctions.h Graphics/Vulkan/DepthImage.cpp Graphics/Vulkan/DepthImage.h Graphics/Vulkan/SwapchainImage.cpp Graphics/Vulkan/SwapchainImage.h Graphics/Vulkan/MemoryCommandBuffer.cpp Graphics/Vulkan/MemoryCommandBuffer.h Graphics/Vulkan/Pipeline.cpp Graphics/Vulkan/Pipeline.h Graphics/Vulkan/Utils.h Graphics/Vulkan/DescriptorType.h Graphics/Vulkan/DescriptorUniformBuffer.cpp Graphics/Vulkan/DescriptorUniformBuffer.h Graphics/Vulkan/Buffer.cpp Graphics/Vulkan/Buffer.h Graphics/Vulkan/DescriptorFunctions.h Graphics/Vulkan/DescriptorImage.cpp Graphics/Vulkan/DescriptorImage.h Graphics/Vulkan/DescriptorPool.cpp Graphics/Vulkan/DescriptorPool.h Graphics/Vulkan/Third-Party/stb_image.h Graphics/Vulkan/Third-Party/stb_image.cpp Graphics/Vulkan/DescriptorSet.cpp Graphics/Vulkan/DescriptorSet.h Graphics/Vulkan/DescriptorSetUniformBuffer.cpp Graphics/Vulkan/DescriptorSetUniformBuffer.h Graphics/Vulkan/DescriptorSetImage.cpp Graphics/Vulkan/DescriptorSetImage.h Graphics/Vulkan/VertexBuffer.h Graphics/Vulkan/IndexBuffer.h Graphics/Vulkan/VertexTypes.h Graphics/Vulkan/UniformBufferType.h Graphics/Vulkan/Mesh.cpp Graphics/Vulkan/Mesh.h Graphics/Window.cpp Graphics/Window.h Core/Program.cpp Core/Program.h Graphics/Vulkan/UIRenderer.cpp Graphics/Vulkan/UIRenderer.h Graphics/Vulkan/UICommandBuffer.cpp Graphics/Vulkan/UICommandBuffer.h Graphics/VulkanHandle.cpp Graphics/VulkanHandle.h Graphics/WindowUtils.h Graphics/WindowHandle.cpp Graphics/WindowHandle.h Graphics/Vulkan/Third-Party/tiny_obj_loader.h Graphics/Vulkan/Third-Party/tiny_obj_loader.cpp Graphics/Context.cpp Graphics/Context.h Graphics/Vulkan/RenderPass.cpp Graphics/Vulkan/RenderPass.h Graphics/Vulkan/PushConstantType.h Graphics/Vulkan/PushConstantFunctions.h Graphics/Vulkan/FrameBuffer.cpp Graphics/Vulkan/FrameBuffer.h Networking/Client.cpp Networking/Client.h Networking/SocketErrors.h Networking/Socket.h Networking/Packet.h Networking/IPv6SocketInfo.h Networking/IPv6ServerSocket.h Networking/IPv6ServerSocket.cpp Networking/IPv6ClientSocket.h Networking/IPv6ClientSocket.cpp Networking/IPv4SocketInfo.h Networking/IPv4ServerSocket.h Networking/IPv4ServerSocket.cpp Networking/IPv4ClientSocket.h Networking/IPv4ClientSocket.cpp Networking/Packet.cpp Graphics/Vulkan/ShaderModule.cpp Graphics/Vulkan/ShaderModule.h Core/TestFile.h Graphics/Vulkan/MAllocator.h Graphics/Vulkan/Logger.h)
endif(APPLE)

if(WIN32)
    add_executable(Vulkan-Abstraction main.cpp Graphics/Vulkan/Instance.cpp Graphics/Vulkan/Instance.h Graphics/Vulkan/Surface.cpp Graphics/Vulkan/Surface.h Graphics/Vulkan/PhysicalDevice.cpp Graphics/Vulkan/PhysicalDevice.h Graphics/Vulkan/LogicalDevice.cpp Graphics/Vulkan/LogicalDevice.h Graphics/Vulkan/Queue.cpp Graphics/Vulkan/Queue.h Graphics/Vulkan/Swapchain.cpp Graphics/Vulkan/Swapchain.h Graphics/Vulkan/Image.cpp Graphics/Vulkan/Image.h Graphics/Vulkan/CommandPool.cpp Graphics/Vulkan/CommandPool.h Graphics/Vulkan/CommandBuffer.cpp Graphics/Vulkan/CommandBuffer.h Graphics/Vulkan/Renderer.cpp Graphics/Vulkan/Renderer.h Graphics/Vulkan/MemoryPool.cpp Graphics/Vulkan/MemoryPool.h Graphics/Vulkan/MemoryFunctions.h Graphics/Vulkan/DepthImage.cpp Graphics/Vulkan/DepthImage.h Graphics/Vulkan/SwapchainImage.cpp Graphics/Vulkan/SwapchainImage.h Graphics/Vulkan/MemoryCommandBuffer.cpp Graphics/Vulkan/MemoryCommandBuffer.h Graphics/Vulkan/Pipeline.cpp Graphics/Vulkan/Pipeline.h Graphics/Vulkan/Utils.h Graphics/Vulkan/DescriptorType.h Graphics/Vulkan/DescriptorUniformBuffer.cpp Graphics/Vulkan/DescriptorUniformBuffer.h Graphics/Vulkan/Buffer.cpp Graphics/Vulkan/Buffer.h Graphics/Vulkan/DescriptorFunctions.h Graphics/Vulkan/DescriptorImage.cpp Graphics/Vulkan/DescriptorImage.h Graphics/Vulkan/DescriptorPool.cpp Graphics/Vulkan/DescriptorPool.h Graphics/Vulkan/Third-Party/stb_image.h Graphics/Vulkan/Third-Party/stb_image.cpp Graphics/Vulkan/DescriptorSet.cpp Graphics/Vulkan/DescriptorSet.h Graphics/Vulkan/DescriptorSetUniformBuffer.cpp Graphics/Vulkan/DescriptorSetUniformBuffer.h Graphics/Vulkan/DescriptorSetImage.cpp Graphics/Vulkan/DescriptorSetImage.h Graphics/Vulkan/VertexBuffer.h Graphics/Vulkan/IndexBuffer.h Graphics/Vulkan/VertexTypes.h Graphics/Vulkan/UniformBufferType.h Graphics/Vulkan/Mesh.cpp Graphics/Vulkan/Mesh.h Graphics/Window.cpp Graphics/Window.h Core/Program.cpp Core/Program.h Graphics/Vulkan/UIRenderer.cpp Graphics/Vulkan/UIRenderer.h Graphics/Vulkan/UICommandBuffer.cpp Graphics/Vulkan/UICommandBuffer.h Graphics/VulkanHandle.cpp Graphics/VulkanHandle.h Graphics/WindowUtils.h Graphics/WindowHandle.cpp Graphics/WindowHandle.h Graphics/Vulkan/Third-Party/tiny_obj_loader.h Graphics/Vulkan/Third-Party/tiny_obj_loader.cpp Graphics/Context.cpp Graphics/Context.h Graphics/Vulkan/RenderPass.cpp Graphics/Vulkan/RenderPass.h Graphics/Vulkan/PushConstantType.h Graphics/Vulkan/PushConstantFunctions.h Graphics/Vulkan/FrameBuffer.cpp Graphics/Vulkan/FrameBuffer.h Graphics/Vulkan/ShaderModule.cpp Graphics/Vulkan/ShaderModule.h Core/TestFile.h Graphics/Vulkan/MAllocator.h Graphics/Vulkan/Logger.h Math/Vector.h Math/Math.h)
endif(WIN32)

if (APPLE)
    set(ENV{VULKAN_SDK} "/Users/michaelferents/Desktop/Vulkan/vulkansdk-macos-1.2.170.0/macOS")

    find_package (Vulkan)
    if (VULKAN_FOUND)
        message(STATUS "Found Vulkan, Including and Linking now")
        include_directories($ENV{VULKAN_SDK}/include)
        target_link_libraries (Vulkan-Abstraction $ENV{VULKAN_SDK}/lib/libvulkan.dylib $ENV{VULKAN_SDK}/lib/libvulkan.1.dylib $ENV{VULKAN_SDK}/lib/libvulkan.1.2.170.dylib)
    endif (VULKAN_FOUND)
endif (APPLE)

if (WIN32)

    find_package(Vulkan REQUIRED)
    target_link_libraries(Vulkan-Abstraction Vulkan::Vulkan)

endif(WIN32)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Third-Party/glfw-3)

target_link_libraries(Vulkan-Abstraction glfw)

add_subdirectory(Third-Party/glm)

target_link_libraries(Vulkan-Abstraction glm)
