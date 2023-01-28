//
// Created by Michael Ferents on 01/03/2022.
//

#ifndef NETWORKING_P2P_SOCKET_H
#define NETWORKING_P2P_SOCKET_H
#include "SocketErrors.h"
#include "Packet.h"

// TCP by standard

namespace Wuu::Networking
{

    class Socket {
    public:

        Socket() = default;

        virtual SocketErrors Create() = 0;
        virtual SocketErrors Read(Packet& packet) = 0;
        virtual SocketErrors Write(Packet& packet) = 0;
        virtual SocketErrors Close() = 0;

        auto& getIdentifier() noexcept { return socketIdentifier; }

    protected:

        int socketIdentifier = 0;

    };

}


#endif //NETWORKING_P2P_SOCKET_H
