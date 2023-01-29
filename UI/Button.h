//
// Created by Michael Ferents on 21/01/2023.
//

#ifndef WUU_BUTTON_H
#define WUU_BUTTON_H
#include "Element.h"
#include <vector>

namespace Wuu
{
    class Button : public Element {
    public:

        Button(std::string title, float x, float y, bool reaction);


    };
}

#endif //WUU_BUTTON_H
