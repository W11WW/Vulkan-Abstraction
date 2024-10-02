//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_DESCRIPTORPOOL_H
#define WUU_DESCRIPTORPOOL_H
#include "LogicalDevice.h"

// TODO: for the moment now lets just stay with only image samplers and uniform buffers

class DescriptorPool {
public:

    DescriptorPool() = default;

    virtual void setPool(LogicalDevice& logicalDevice, size_t uniformBufferSize, size_t imageSamplerSize, size_t setCount);
    virtual void destroy(LogicalDevice& logicalDevice);

    [[nodiscard]] inline auto& getPool() noexcept { return m_descriptorPool; }

    [[nodiscard]] const auto& getUniformBufferSize() const noexcept { return m_uniformBufferSize; }
    [[nodiscard]] const auto& getImageSamplerSize() const noexcept { return m_imageSamplerSize; }
    [[nodiscard]] const auto& getSetCount() const noexcept { return m_setCount; }

protected:

    vk::DescriptorPool m_descriptorPool;

    size_t m_uniformBufferSize = 0;
    size_t m_imageSamplerSize = 0;
    size_t m_setCount = 0;

};


#endif //WUU_DESCRIPTORPOOL_H
