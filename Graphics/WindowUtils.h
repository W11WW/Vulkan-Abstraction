//
// Created by Michael Ferents on 06/04/2022.
//

#ifndef WUU_WINDOWSUTILS_H
#define WUU_WINDOWSUTILS_H

#include <iostream>

class WindowCallbackInfo {
public:

    double mouseXpos = 0;
    double mouseYpos = 0;

    int keyboardKeyPressed = -1;
    int keyboardKeyAction = -1;

    int mouseButtonPressed = -1;
    int mouseButtonAction = -1;

    double mouseScrollXoffset = 0;
    double mouseScrollYoffset = 0;

    void reset()
    {
        mouseXpos = 0;
        mouseYpos = 0;

        keyboardKeyPressed = -1;
        keyboardKeyAction = -1;

        mouseButtonPressed = -1;
        mouseButtonAction = -1;

        mouseScrollXoffset = 0;
        mouseScrollYoffset = 0;
    }
};

#endif //WUU_WINDOWSUTILS_H
