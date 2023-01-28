//
// Created by Michael Ferents on 02/03/2022.
//

#ifndef NETWORKING_P2P_IPV6SOCKETINFO_H
#define NETWORKING_P2P_IPV6SOCKETINFO_H
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Wuu::Networking
{

    class IPv6SocketInfo final {
    public:

        IPv6SocketInfo() = default;

        using SocketInfo = struct sockaddr_in6;

        auto& getInfo() noexcept { return m_info; }
        auto& getAddress() noexcept { return m_IPv6Address; }
        auto& getPort() noexcept { return m_port; }

    private:

        std::string m_IPv6Address;
        int m_port = 0;

        SocketInfo m_info {};

    };

}

#endif //NETWORKING_P2P_IPV6SOCKETINFO_H
