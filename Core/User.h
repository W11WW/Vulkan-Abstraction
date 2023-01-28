//
// Created by Michael Ferents on 26/03/2022.
//

#ifndef WUU_USER_H
#define WUU_USER_H
#include "Util.h"
#include <vector>
#include "Networking/Packet.h"

namespace Wuu
{
    class User {
    public:

        User() = default;

    private:

        Status m_userStatusTest;

        std::vector<Networking::Packet> m_recordedMessages;

    };
}

#endif //WUU_USER_H
