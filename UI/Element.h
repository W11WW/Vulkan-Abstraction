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
    [[nodiscard]] const auto& getID() const noexcept { return m_ID; }
    [[nodiscard]] const auto& getVisibility() const noexcept { return m_visibility; }

    void setPosition(glm::vec3&& newPosition) noexcept { m_position = newPosition; }
    void setID(auto&& visibility) noexcept { m_visibility = visibility; }
    void setVisibility(auto&& newID) noexcept { m_ID = newID; }

protected:

    glm::vec3 m_position;
    bool m_visibility = true;
    std::string m_ID = "Default";

};


#endif //WUU_ELEMENT_H
