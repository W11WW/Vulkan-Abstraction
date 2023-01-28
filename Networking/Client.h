//
// Created by Michael Ferents on 22/03/2022.
//

#ifndef WUU_CLIENT_H
#define WUU_CLIENT_H

#include "IPv4ClientSocket.h"

namespace Wuu::Networking
{

    class Client {
    public:

        Client() = default;

        void run();

    private:

        IPv4ClientSocket clientSocket {};

    };
}


#endif //WUU_CLIENT_H
