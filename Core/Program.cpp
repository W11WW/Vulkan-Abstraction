//
// Created by Michael Ferents on 21/03/2022.
//

#include "Program.h"

using namespace Wuu;

void Program::run()
{
    //std::thread NetworkingThread(&Networking::Client::run, &client);

    window.initialize();

    window.run();

    //NetworkingThread.join();
}

void Program::destroy()
{
    window.destroy();
}