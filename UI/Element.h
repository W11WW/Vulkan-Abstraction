//
// Created by Michael Ferents on 23/03/2022.
//

#ifndef WUU_ELEMENT_H
#define WUU_ELEMENT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Element {
public:

    Element() = default;

    [[nodiscard]] const auto& getPosition() const noexcept { return m_position; }

    void setPosition(glm::vec3&& newPosition) noexcept { m_position = newPosition; }

protected:

    glm::vec3 m_position;

};


#endif //WUU_ELEMENT_H
