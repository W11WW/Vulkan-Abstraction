//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_PROGRAM_H
#define WUU_PROGRAM_H
#include "UI/Window.h"
#include "Networking/Client.h"
#include "Data.h"
#include <thread>

namespace Wuu {

    class Program {
    public:

        Program() = default;

        void run();
        void destroy();

    private:

        Window window {};
        Networking::Client client {};

        Data dataStructure {};

    };

}


#endif //WUU_PROGRAM_H
