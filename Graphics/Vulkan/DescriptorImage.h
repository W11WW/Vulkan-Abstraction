//
// Created by Michael Ferents on 14/03/2022.
//

#ifndef WUU_DESCRIPTORIMAGE_H
#define WUU_DESCRIPTORIMAGE_H
#include "Image.h"
#include "MemoryFunctions.h"
#include "DescriptorType.h"

// TODO: look into what sampler is and does, make image more customizable later

class DescriptorImage : public Image, public DescriptorType {
public:

    DescriptorImage() : Image(), DescriptorType() {}

    virtual void setImage(LogicalDevice& logicalDevice, PhysicalDevice& physicalDevice, MemoryPool& memoryPool, std::string fileName);

    [[nodiscard]] auto& getSampler() noexcept { return m_sampler; }

protected:

    vk::Sampler m_sampler;

};


#endif //WUU_DESCRIPTORIMAGE_H
