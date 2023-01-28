//
// Created by Michael Ferents on 02/03/2022.
//

#include "IPv4ServerSocket.h"

using namespace Wuu::Networking;

SocketErrors IPv4ServerSocket::Create()
{
    // TCP by standard
    socketIdentifier = socket(AF_INET, SOCK_STREAM, 0);
    return SocketErrors::SUCCESS;
}

// Can give error
SocketErrors IPv4ServerSocket::Close()
{
    close(socketIdentifier);
    return SocketErrors::SUCCESS;
}

SocketErrors IPv4ServerSocket::Read(Packet& packet)
{
    char recvline[4095];
    ssize_t n = read(socketIdentifier, recvline, 4096);
    recvline[n] = 0;

    packet.setData(recvline);

    return SocketErrors::SUCCESS;
}
// For now we assume size of packet is only 4096 characters
// Perhaps we dont need a write for a server socket ?
SocketErrors IPv4ServerSocket::Write(Packet& packet)
{
    char buffer[4096];

    return SocketErrors::SUCCESS;
}

// Potential error when converting text IP to binary
void IPv4ServerSocket::setSocketInfo(std::string_view IPv4Address, const sa_family_t family, const int port) noexcept
{
    // Set structure to 0
    bzero(&m_socketInfo.getInfo(), sizeof(m_socketInfo.getInfo()));
    // Set ip address and convert but if not than just 0.0.0.0 ... ect
    if(IPv4Address.length() > 1)
    {
        m_socketInfo.getAddress() = IPv4Address;
        inet_pton(AF_INET, m_socketInfo.getAddress().c_str(), &m_socketInfo.getInfo().sin_addr);
    }
    m_socketInfo.getPort() = port;
    m_socketInfo.getInfo().sin_port = htons(port);
    m_socketInfo.getInfo().sin_family = family;
}
// Potential error
SocketErrors IPv4ServerSocket::Bind()
{
    bind(socketIdentifier, reinterpret_cast<struct sockaddr *>(&m_socketInfo.getInfo()), sizeof(m_socketInfo.getInfo()));
    return SocketErrors::SUCCESS;
}
// not sure what backlog(1024) means perhaps its how many socks can try connecting at once
SocketErrors IPv4ServerSocket::Listen()
{
    listen(socketIdentifier, 1024);
    return SocketErrors::SUCCESS;
}

int IPv4ServerSocket::Accept()
{
    return accept(socketIdentifier, (struct sockaddr*) nullptr, nullptr);
}