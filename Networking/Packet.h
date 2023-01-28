//
// Created by Michael Ferents on 02/03/2022.
//

#ifndef NETWORKING_P2P_PACKET_H
#define NETWORKING_P2P_PACKET_H
#include <iostream>
#include <string>

namespace Wuu::Networking
{

    class Packet {
    public:

        Packet() = default;

        virtual void setData(const std::string& data)
        {
            m_data = data;
            m_dataSize = data.length();
        }

        // Not sure why a new line is placed after we print the data ?
        friend std::ostream& operator<<(std::ostream& os, const Packet& pck)
        {
            os << "Data: " << pck.m_data;
            os << "Data Size: " << pck.m_dataSize << "\n";
            return os;
        }

        auto& getData() noexcept { return m_data; }
        auto& getDataSize() noexcept { return m_dataSize; }

    protected:

        std::string m_data;
        std::size_t m_dataSize = 0;
    };

}

#endif //NETWORKING_P2P_PACKET_H
