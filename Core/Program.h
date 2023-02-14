//
// Created by Michael Ferents on 21/03/2022.
//

#ifndef WUU_PROGRAM_H
#define WUU_PROGRAM_H
#include "UI/Window.h"

#if defined(__APPLE__)
    #include "Networking/Client.h"
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)

#endif

#include "Data.h"
#include <thread>

namespace Wuu {

    class Program {
    public:

        Program() = default;

        void run();
        void destroy();

    private:

        UI::Window window {};

        //std::thread NetworkingThread(&Networking::Client::run, &client);
        //Networking::Client client {};

        Data dataStructure {};

    };

}


#endif //WUU_PROGRAM_H
