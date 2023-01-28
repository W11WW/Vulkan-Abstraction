//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_GENERALCOMMANDBUFFER_H
#define WUU_GENERALCOMMANDBUFFER_H
#include "CommandBuffer.h"

namespace Wuu::Vulkan {

    class GeneralCommandBuffer : public CommandBuffer {
    public:

        GeneralCommandBuffer() = default;

        void beginCommandBufferRecord() final;
        void endCommandBufferRecord() final;
        void recordObject();

    };

}


#endif //WUU_GENERALCOMMANDBUFFER_H
