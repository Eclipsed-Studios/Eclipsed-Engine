#pragma once

#include "NetworkEngine/Shared/Message.h"

namespace Eclipse::Replication
{
    class ReplicationHelper
    {
    public:
        ReplicationHelper() = default;
        ~ReplicationHelper() = default;

        static void RecieveAddComponentMessage(const NetMessage& message);
        static void RecieveCreateObjectMessage(const NetMessage& message);
        static void RecieveVariableMessage(const NetMessage& message);
        
        static void HandleRecieve(const NetMessage& message);
    };

}