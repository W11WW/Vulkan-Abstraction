//
// Created by Michael Ferents on 14/07/2023.
//

#include "ShaderModule.h"

void ShaderModule::initialize(LogicalDevice &logicalDevice)
{
    auto shaderCode = readFile(m_shaderPath);

    auto shaderCreateInfo =
            vk::ShaderModuleCreateInfo{{}, shaderCode.size(),
                                       reinterpret_cast<const uint32_t *>(shaderCode.data())};

    m_shaderModule = logicalDevice.getLogicalDevice().createShaderModule(shaderCreateInfo);
}