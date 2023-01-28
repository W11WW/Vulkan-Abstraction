cmake_minimum_required(VERSION 3.20)
project(Wuu)

set(CMAKE_CXX_STANDARD 20)

add_executable(Wuu main.cpp UI/Vulkan/Instance.cpp UI/Vulkan/Instance.h UI/Vulkan/Surface.cpp UI/Vulkan/Surface.h UI/Vulkan/PhysicalDevice.cpp UI/Vulkan/PhysicalDevice.h UI/Vulkan/LogicalDevice.cpp UI/Vulkan/LogicalDevice.h UI/Vulkan/Queue.cpp UI/Vulkan/Queue.h UI/Vulkan/Swapchain.cpp UI/Vulkan/Swapchain.h UI/Vulkan/Image.cpp UI/Vulkan/Image.h UI/Vulkan/CommandPool.cpp UI/Vulkan/CommandPool.h UI/Vulkan/CommandBuffer.cpp UI/Vulkan/CommandBuffer.h UI/Vulkan/Renderer.cpp UI/Vulkan/Renderer.h UI/Vulkan/GeneralCommandBuffer.cpp UI/Vulkan/GeneralCommandBuffer.h UI/Vulkan/GeneralRenderer.cpp UI/Vulkan/GeneralRenderer.h UI/Vulkan/MemoryPool.cpp UI/Vulkan/MemoryPool.h UI/Vulkan/MemoryFunctions.h UI/Vulkan/DepthImage.cpp UI/Vulkan/DepthImage.h UI/Vulkan/SwapchainImage.cpp UI/Vulkan/SwapchainImage.h UI/Vulkan/MemoryCommandBuffer.cpp UI/Vulkan/MemoryCommandBuffer.h UI/Vulkan/Shader.cpp UI/Vulkan/Shader.h UI/Vulkan/Utils.h UI/Vulkan/DescriptorType.h UI/Vulkan/DescriptorUniformBuffer.cpp UI/Vulkan/DescriptorUniformBuffer.h UI/Vulkan/Buffer.cpp UI/Vulkan/Buffer.h UI/Vulkan/DescriptorFunctions.h UI/Vulkan/DescriptorImage.cpp UI/Vulkan/DescriptorImage.h UI/Vulkan/DescriptorPool.cpp UI/Vulkan/DescriptorPool.h UI/Vulkan/stb_image.h UI/Vulkan/stb_image.cpp UI/Vulkan/DescriptorSet.cpp UI/Vulkan/DescriptorSet.h UI/Vulkan/DescriptorSetUniformBuffer.cpp UI/Vulkan/DescriptorSetUniformBuffer.h UI/Vulkan/DescriptorSetImage.cpp UI/Vulkan/DescriptorSetImage.h UI/Vulkan/VertexBuffer.h UI/Vulkan/IndexBuffer.h UI/Vulkan/VertexTypes.h UI/Vulkan/UniformBufferType.h UI/Vulkan/Shape.cpp UI/Vulkan/Shape.h UI/Window.cpp UI/Window.h Core/Program.cpp Core/Program.h Networking/Client.cpp Networking/Client.h Networking/SocketErrors.h Networking/Socket.h Networking/Packet.h Networking/IPv6SocketInfo.h Networking/IPv6ServerSocket.h Networking/IPv6ServerSocket.cpp Networking/IPv6ClientSocket.h Networking/IPv6ClientSocket.cpp Networking/IPv4SocketInfo.h Networking/IPv4ServerSocket.h Networking/IPv4ServerSocket.cpp Networking/IPv4ClientSocket.h Networking/IPv4ClientSocket.cpp Networking/Packet.cpp Core/Data.cpp Core/Data.h UI/Element.h UI/Vulkan/UIRenderer.cpp UI/Vulkan/UIRenderer.h UI/Vulkan/ElementCommandBuffer.cpp UI/Vulkan/ElementCommandBuffer.h Core/DataGuard.h Core/User.cpp Core/User.h Core/Util.h UI/VulkanHandle.cpp UI/VulkanHandle.h UI/WindowUtils.h UI/WindowHandle.cpp UI/WindowHandle.h UI/Vulkan/tiny_obj_loader.h UI/Vulkan/tiny_obj_loader.cpp UI/Button.cpp UI/Button.h)

set(ENV{VULKAN_SDK} "/Users/michaelferents/Desktop/Vulkan/vulkansdk-macos-1.2.170.0/macOS")

find_package (Vulkan)
if (VULKAN_FOUND)
    message(STATUS "Found Vulkan, Including and Linking now")
    include_directories($ENV{VULKAN_SDK}/include)
    target_link_libraries (Wuu $ENV{VULKAN_SDK}/lib/libvulkan.dylib $ENV{VULKAN_SDK}/lib/libvulkan.1.dylib $ENV{VULKAN_SDK}/lib/libvulkan.1.2.170.dylib)
endif (VULKAN_FOUND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3)

target_link_libraries(Wuu glfw)

add_subdirectory(glm)

target_link_libraries(Wuu glm)
