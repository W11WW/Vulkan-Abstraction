//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_SURFACE_H
#define WUU_SURFACE_H
#include "Instance.h"

class Surface {
public:

    Surface() = default;

    virtual void initializeSurface(Instance& instance, GLFWwindow* window);
    virtual void destroy(Instance& instance);

    [[nodiscard]] const auto& getSurface() const noexcept { return m_surface; }

protected:

    vk::SurfaceKHR m_surface;

};

#endif //WUU_SURFACE_H
