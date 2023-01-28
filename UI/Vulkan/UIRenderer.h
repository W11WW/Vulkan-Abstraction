//
// Created by Michael Ferents on 23/03/2022.
//

#ifndef WUU_UIRENDERER_H
#define WUU_UIRENDERER_H
#include "Renderer.h"
#include "ElementCommandBuffer.h"

namespace Wuu::Vulkan
{

    class UIRenderer : public Renderer{
    public:

        UIRenderer() = default;

        ~UIRenderer();

        void initialize(GLFWwindow* window);

        bool render(GLFWwindow* window) final;

        [[nodiscard]] auto& getCommandBuffers() noexcept { return m_commandBuffers; }

    private:

        CommandPool m_commandPool;

        std::vector<ElementCommandBuffer> m_commandBuffers;

        vk::Semaphore m_imageAvailableSemaphore;
        vk::Semaphore m_renderFinishedSemaphore;

        void recreateSwapchain(GLFWwindow* window);

    };

}


#endif //WUU_UIRENDERER_H
