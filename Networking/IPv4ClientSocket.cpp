//
// Created by Michael Ferents on 01/03/2022.
//

// Test

#include "IPv4ClientSocket.h"

using namespace Wuu::Networking;

SocketErrors IPv4ClientSocket::Create()
{
    // TCP by standard
    socketIdentifier = socket(AF_INET, SOCK_STREAM, 0);
    return SocketErrors::SUCCESS;
}

// Can give error
SocketErrors IPv4ClientSocket::Close()
{
    close(socketIdentifier);
    return SocketErrors::SUCCESS;
}

SocketErrors IPv4ClientSocket::Read(Packet& packet)
{
    char recvline[4095];
    ssize_t n = read(socketIdentifier, recvline, 4096);
    recvline[n] = 0;

    packet.setData(recvline);

    return SocketErrors::SUCCESS;
}

SocketErrors IPv4ClientSocket::Write(Packet& packet)
{
    write(socketIdentifier, packet.getData().c_str(), packet.getDataSize());
    return SocketErrors::SUCCESS;
}

// Potential error when converting text IP to binary
void IPv4ClientSocket::setSocketInfo(std::string_view IPv4Address, const sa_family_t family, const int port) noexcept
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

SocketErrors IPv4ClientSocket::Connect()
{
    int d;
    d = connect(socketIdentifier, reinterpret_cast<struct sockaddr *>(&m_socketInfo.getInfo()), sizeof(m_socketInfo.getInfo()));
    return SocketErrors::SUCCESS;
}