//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_COMMANDBUFFER_H
#define WUU_COMMANDBUFFER_H
#include "CommandPool.h"

class CommandBuffer {
public:

    CommandBuffer() = default;

    virtual void setBuffer(LogicalDevice& logicalDevice, CommandPool& commandPool, const vk::CommandBufferLevel commandBufferLevel);
    virtual void destroy(LogicalDevice& logicalDevice, CommandPool& commandPool);

    virtual void beginCommandBufferRecord() = 0;
    virtual void endCommandBufferRecord() = 0;

    [[nodiscard]] auto& getCommandBuffer() noexcept { return m_commandBuffer; }

protected:

    vk::CommandBuffer m_commandBuffer;

};


#endif //WUU_COMMANDBUFFER_H
