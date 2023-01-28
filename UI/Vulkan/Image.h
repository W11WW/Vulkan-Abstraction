//
// Created by Michael Ferents on 11/03/2022.
//

#ifndef WUU_IMAGE_H
#define WUU_IMAGE_H
#include "LogicalDevice.h"

// TODO: check when destroying if u can

namespace Wuu::Vulkan {

    class Image {
    public:

        Image() = default;

        virtual void destroy(LogicalDevice& logicalDevice);

        [[nodiscard]] auto& getImage() noexcept { return m_image; }
        [[nodiscard]] auto& getImageView() noexcept { return m_imageView; }
        [[nodiscard]] auto& getDeviceMemory() noexcept { return m_deviceMemory; }

    protected:

        vk::Image m_image;
        vk::ImageView m_imageView;
        vk::DeviceMemory m_deviceMemory;

    };

}


#endif //WUU_IMAGE_H
