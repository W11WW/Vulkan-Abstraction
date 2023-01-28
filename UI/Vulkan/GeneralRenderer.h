//
// Created by Michael Ferents on 12/03/2022.
//

#ifndef WUU_GENERALRENDERER_H
#define WUU_GENERALRENDERER_H
#include "Renderer.h"
#include "GeneralCommandBuffer.h"


// TODO: eventually change from explicit to implicit
namespace Wuu::Vulkan {

    class GeneralRenderer : public Renderer {
    public:

        explicit GeneralRenderer(GLFWwindow* window);

        ~GeneralRenderer();

        bool render(GLFWwindow* window) final;

        [[nodiscard]] auto& getCommandBuffers() noexcept { return m_commandBuffers; }
    private:

        CommandPool m_commandPool;

        std::vector<GeneralCommandBuffer> m_commandBuffers;

        vk::Semaphore m_imageAvailableSemaphore;
        vk::Semaphore m_renderFinishedSemaphore;

        void recreateSwapchain(GLFWwindow* window);

    };

}


#endif //WUU_GENERALRENDERER_H
