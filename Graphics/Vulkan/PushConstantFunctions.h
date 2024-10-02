//
// Created by Michael Ferents on 31/01/2023.
//

#ifndef WUU_PUSHCONSTANTFUNCTIONS_H
#define WUU_PUSHCONSTANTFUNCTIONS_H

#include "PushConstantType.h"

static inline void createPushConstantObject(PushConstantData& ubo, glm::vec3 position) noexcept
{
    ubo.model = glm::mat4(1.0f);
    ubo.model = glm::translate(ubo.model, position);
    ubo.model = glm::scale(ubo.model, glm::vec3 (0.7f, 0.7f, 0.7f));
}

#endif //WUU_PUSHCONSTANTFUNCTIONS_H
