//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_UNIFORMBUFFERTYPE_H
#define WUU_UNIFORMBUFFERTYPE_H

#include "Third-Party/glm/glm.hpp"
#include "Third-Party/glm/gtc/matrix_transform.hpp"

struct UniformBufferObject
{
    
    glm::mat4 view;
    glm::mat4 proj;

};

#endif //WUU_UNIFORMBUFFERTYPE_H
