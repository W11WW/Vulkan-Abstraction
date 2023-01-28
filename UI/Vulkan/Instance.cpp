//
// Created by Michael Ferents on 10/03/2022.
//

#include "Instance.h"

using namespace Wuu::Vulkan;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
}

void Instance::initializeInstance()
{

    vk::ApplicationInfo applicationInfo(m_info.m_applicationName.c_str(),
                                        m_info.m_applicationVersion,
                                        m_info.m_engineName.c_str(),
                                        m_info.m_engineVersion,
                                        VK_API_VERSION_1_0);

    auto glfwExtensionCount = 0u;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> glfwExtensionsVector(glfwExtensions, glfwExtensions + glfwExtensionCount);
    auto layers = std::vector<const char*> { "VK_LAYER_KHRONOS_validation" };

    vk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    if(m_info.m_enableValidationLayers)
    {
        glfwExtensionsVector.push_back("VK_EXT_debug_utils");
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        instanceCreateInfo.ppEnabledLayerNames = layers.data();
    } else
    {
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.ppEnabledLayerNames = nullptr;
    }
    glfwExtensionsVector.push_back("VK_KHR_get_physical_device_properties2");

    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensionsVector.data();
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensionsVector.size());
    m_instance = vk::createInstance( instanceCreateInfo );

    if(m_info.m_enableValidationLayers)
    {
        auto dldi = vk::DispatchLoaderDynamic(m_instance, vkGetInstanceProcAddr);

        m_debugUtilsMessengerEXT = m_instance.createDebugUtilsMessengerEXT(
                vk::DebugUtilsMessengerCreateInfoEXT {
                        {},
                        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
                                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
                                debugCallback
                },
                nullptr, dldi
                );
    }

}

void Instance::destroy()
{
    m_instance.destroy();
}