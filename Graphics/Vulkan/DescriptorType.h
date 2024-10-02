//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_DESCRIPTORTYPE_H
#define WUU_DESCRIPTORTYPE_H

#include <vulkan/vulkan.hpp>

// TODO: eventually add dstArrayElement for descriptor sets

class DescriptorType {
public:

    DescriptorType() = default;

    void setBinding(std::size_t&& binding) noexcept { m_binding = binding; }
    void setType(vk::DescriptorType&& type) noexcept { m_type = type; }
    void setShaderStage(vk::ShaderStageFlagBits&& shaderStage) noexcept { m_shaderStage = shaderStage; }

    auto& getBinding() noexcept { return m_binding; }
    auto& getType() noexcept { return m_type; }
    auto& getShaderStage() noexcept { return m_shaderStage; }

protected:

    std::size_t m_binding;
    vk::DescriptorType m_type;
    vk::ShaderStageFlagBits m_shaderStage;

};

#endif //WUU_DESCRIPTORTYPE_H
