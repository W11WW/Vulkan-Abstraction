//
// Created by Michael Ferents on 01/03/2022.
//

#ifndef NETWORKING_P2P_IPV6CLIENTSOCKET_H
#define NETWORKING_P2P_IPV6CLIENTSOCKET_H
#include "Socket.h"
#include "IPv6SocketInfo.h"

namespace Wuu::Networking
{

    class IPv6ClientSocket : public Socket {
    public:

        IPv6ClientSocket() = default;

        SocketErrors Create() final;

        SocketErrors Read(Packet& packet) override;
        SocketErrors Write(Packet& packet) override;

        SocketErrors Close() final;

        SocketErrors Connect();

        auto& getSocketInfo() noexcept { return m_socketInfo; }
        void setSocketInfo(std::string_view IPv6Address, sa_family_t family, int port) noexcept;

    protected:

        IPv6SocketInfo m_socketInfo;

    };

}


#endif //NETWORKING_P2P_IPV6CLIENTSOCKET_H
