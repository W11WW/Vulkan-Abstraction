//
// Created by Michael Ferents on 14/07/2023.
//

#ifndef WUU_SHADERMODULE_H
#define WUU_SHADERMODULE_H
#include <vulkan/vulkan.hpp>
#include "LogicalDevice.h"
#include "Utils.h"

class ShaderModule {
public:

    ShaderModule() = default;

    virtual void initialize(LogicalDevice& logicalDevice);

    void setShaderPath(std::string_view shaderPath) noexcept { m_shaderPath = shaderPath; }
    void setShaderStage(vk::ShaderStageFlagBits shaderStage) noexcept { m_shaderStage = shaderStage; }
    void setEntryPointName(std::string_view name) noexcept { m_entryPointName = name; }

    [[nodiscard]] auto& getModule() noexcept { return m_shaderModule; }
    auto& getShaderStage() noexcept { return m_shaderStage; }
    auto& getEntryPointName() noexcept { return m_entryPointName; }

protected:

    std::string m_shaderPath;
    std::string m_entryPointName;

    vk::ShaderStageFlagBits m_shaderStage;

    vk::ShaderModule m_shaderModule;
};


#endif //WUU_SHADERMODULE_H
