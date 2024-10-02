//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_VERTEXBUFFER_H
#define WUU_VERTEXBUFFER_H
#include "Buffer.h"

class VertexBuffer : public Buffer {
public:

    VertexBuffer() : Buffer() {}

    [[nodiscard]] auto& getVerticesSize() noexcept { return m_verticesSize; }

protected:

    uint32_t m_verticesSize = 0;

};


#endif //WUU_VERTEXBUFFER_H
