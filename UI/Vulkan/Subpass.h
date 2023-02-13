//
// Created by Michael Ferents on 07/02/2023.
//

#ifndef WUU_SUBPASS_H
#define WUU_SUBPASS_H
#include <vector>
#include <vulkan/vulkan.hpp>

namespace Wuu::Vulkan
{

    // chnage setDescription eventually

    class Subpass {
    public:

        Subpass() = default;

        void setDescription() noexcept;

        [[nodiscard]] auto& getAttachmentDescriptions() noexcept { return m_attachmentDescriptions; }
        [[nodiscard]] const auto& getAttachmentDescriptions() const noexcept { return m_attachmentDescriptions; }

    private:

        vk::SubpassDescription m_subpassDescription;
        vk::SubpassDependency m_subpassDependency;

        std::vector<vk::AttachmentDescription> m_attachmentDescriptions;

    };
}

#endif //WUU_SUBPASS_H
