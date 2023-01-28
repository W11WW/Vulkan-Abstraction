//
// Created by Michael Ferents on 12/03/2022.
//

#include "GeneralCommandBuffer.h"

using namespace Wuu::Vulkan;

void GeneralCommandBuffer::beginCommandBufferRecord()
{
    auto beginInfo = vk::CommandBufferBeginInfo {};
    m_commandBuffer.begin(beginInfo);
}

void GeneralCommandBuffer::recordObject()
{

}

void GeneralCommandBuffer::endCommandBufferRecord()
{
    m_commandBuffer.end();
}