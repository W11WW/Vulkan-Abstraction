//
// Created by Michael Ferents on 13/03/2022.
//

#ifndef WUU_SWAPCHAINIMAGE_H
#define WUU_SWAPCHAINIMAGE_H
#include "Image.h"

class SwapchainImage : public Image {
public:

    SwapchainImage() = default;

    void setImage(vk::Image image, LogicalDevice& logicalDevice, vk::Format format);

};


#endif //WUU_SWAPCHAINIMAGE_H
