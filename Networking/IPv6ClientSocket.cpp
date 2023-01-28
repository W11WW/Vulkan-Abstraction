//
// Created by Michael Ferents on 01/03/2022.
//

#include "IPv6ClientSocket.h"

using namespace Wuu::Networking;

SocketErrors IPv6ClientSocket::Create()
{
    // TCP by standard
    socketIdentifier = socket(AF_INET6, SOCK_STREAM, 0);
    return SocketErrors::SUCCESS;
}

SocketErrors IPv6ClientSocket::Close()
{
    close(socketIdentifier);
    return SocketErrors::SUCCESS;
}

SocketErrors IPv6ClientSocket::Read(Packet& packet)
{
    char recvline[4095];
    ssize_t n = read(socketIdentifier, recvline, 4096);
    recvline[n] = 0;

    packet.setData(recvline);

    return SocketErrors::SUCCESS;
}
// For now we assume size of packet is only 4096 characters
SocketErrors IPv6ClientSocket::Write(Packet& packet)
{
    write(socketIdentifier, packet.getData().c_str(), packet.getDataSize());
    return SocketErrors::SUCCESS;
}

// Potential error when converting text IP to binary
void IPv6ClientSocket::setSocketInfo(std::string_view IPv6Address, sa_family_t family, int port) noexcept
{
    // Set structure to 0
    bzero(&m_socketInfo.getInfo(), sizeof(m_socketInfo.getInfo()));
    // Set ip address and convert but if not than just 0.0.0.0 ... ect
    if(IPv6Address.length() > 1)
    {
        m_socketInfo.getAddress() = IPv6Address;
        inet_pton(AF_INET6, m_socketInfo.getAddress().c_str(), &m_socketInfo.getInfo().sin6_addr);
    }
    m_socketInfo.getPort() = port;
    m_socketInfo.getInfo().sin6_port = htons(port);
    m_socketInfo.getInfo().sin6_family = family;
}

SocketErrors IPv6ClientSocket::Connect()
{
    int d;
    d = connect(socketIdentifier, reinterpret_cast<struct sockaddr *>(&m_socketInfo.getInfo()), sizeof(m_socketInfo.getInfo()));
    return SocketErrors::SUCCESS;
}