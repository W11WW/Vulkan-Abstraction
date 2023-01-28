//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_INDEXBUFFER_H
#define WUU_INDEXBUFFER_H
#include "Buffer.h"

namespace Wuu::Vulkan {

    class IndexBuffer : public Buffer {
    public:

        IndexBuffer() : Buffer() {}

        [[nodiscard]] auto& getIndicesSize() noexcept { return m_indicesSize; }

    protected:

        uint32_t m_indicesSize = 0;

    };

}


#endif //WUU_INDEXBUFFER_H
