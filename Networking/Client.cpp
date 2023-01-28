//
// Created by Michael Ferents on 22/03/2022.
//

#include "Client.h"

using namespace Wuu::Networking;

void Client::run()
{
    clientSocket.Create();

    clientSocket.setSocketInfo("", AF_INET, 13);

    clientSocket.Connect();

    Packet packet {};

    clientSocket.Read(packet);

    std::cout << packet;
}