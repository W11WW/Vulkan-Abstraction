//
// Created by Michael Ferents on 23/03/2022.
//

#ifndef WUU_UIRENDERER_H
#define WUU_UIRENDERER_H
#include "Renderer.h"
#include "BasicCommandBuffer.h"

#include <array>

class BasicRenderer : public Renderer{
public:

    BasicRenderer() = default;

    ~BasicRenderer();

    void initialize(GLFWwindow* window);

    bool render(GLFWwindow* window) final;

    [[nodiscard]] auto& getCommandBuffers() noexcept { return m_commandBuffers; }
    [[nodiscard]] auto& getCommandPool() noexcept { return m_commandPool; }

private:

    CommandPool m_commandPool;

    std::vector<std::array<BasicCommandBuffer, 2>> m_commandBuffers;

    vk::Semaphore m_imageAvailableSemaphore;
    vk::Semaphore m_renderFinishedSemaphore;

    void recreateSwapchain(GLFWwindow* window);

};


#endif //WUU_UIRENDERER_H
