//
// Created by Michael Ferents on 17/03/2022.
//

#ifndef WUU_DESCRIPTORSET_H
#define WUU_DESCRIPTORSET_H
#include <vulkan/vulkan.hpp>
#include "Shader.h"
#include "DescriptorPool.h"
#include "LogicalDevice.h"
#include "VertexTypes.h"

// NOTE: when descriptor pool is destroyed all sets are aswell

namespace Wuu::Vulkan {

    class DescriptorSet {
    public:

        DescriptorSet() = default;

        void initialize(LogicalDevice& logicalDevice, DescriptorPool& pool, vk::DescriptorSetLayout& layout);

        [[nodiscard]] inline const auto& getDescriptorSet() const noexcept { return m_descriptorSet; }

    protected:

        vk::DescriptorSet m_descriptorSet;

    };

}


#endif //WUU_DESCRIPTORSET_H
