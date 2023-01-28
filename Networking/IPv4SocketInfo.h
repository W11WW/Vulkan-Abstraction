//
// Created by Michael Ferents on 01/03/2022.
//

#ifndef NETWORKING_P2P_IPV4SOCKETINFO_H
#define NETWORKING_P2P_IPV4SOCKETINFO_H
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Wuu::Networking
{

    class IPv4SocketInfo final {
    public:

        IPv4SocketInfo() = default;

        using SocketInfo = struct sockaddr_in;

        auto& getInfo() noexcept { return m_info; }
        auto& getAddress() noexcept { return m_IPv4Address; }
        auto& getPort() noexcept { return m_port; }

    private:

        std::string m_IPv4Address;
        int m_port = 0;

        SocketInfo m_info {};

    };

}

#endif //NETWORKING_P2P_IPV4SOCKETINFO_H
