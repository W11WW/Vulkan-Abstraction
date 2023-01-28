//
// Created by Michael Ferents on 02/03/2022.
//

#ifndef NETWORKING_P2P_IPV4SERVERSOCKET_H
#define NETWORKING_P2P_IPV4SERVERSOCKET_H
#include "Socket.h"
#include "IPv4SocketInfo.h"

namespace Wuu::Networking
{

    class IPv4ServerSocket : public Socket {
    public:

        IPv4ServerSocket() = default;

        SocketErrors Create() final;

        SocketErrors Read(Packet& packet) override;
        SocketErrors Write(Packet& packet) override;

        SocketErrors Close() final;

        SocketErrors Bind();
        SocketErrors Listen();
        int Accept();

        auto& getSocketInfo() noexcept { return m_socketInfo; }
        void setSocketInfo(std::string_view IPv4Address, const sa_family_t family, const int port) noexcept;

    protected:

        IPv4SocketInfo m_socketInfo;

    };

}


#endif //NETWORKING_P2P_IPV4SERVERSOCKET_H
