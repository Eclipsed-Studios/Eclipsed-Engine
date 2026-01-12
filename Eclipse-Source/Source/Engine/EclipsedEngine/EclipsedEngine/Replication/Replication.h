#pragma once

#include "NetworkEngine/Shared/Message.h"

namespace Eclipse
{
    class Component;
}

namespace Eclipse::Replication
{
    class ReplicationHelper
    {
    public:
        class ClientHelp
        {
        public:
            static void RecieveStartRecievedComponents(const NetMessage& message);
            static void RecieveAddComponentMessage(const NetMessage& message);
            static void RecieveCreateObjectMessage(const NetMessage& message);
            static void RecieveDeleteObjectMessage(const NetMessage& message);
            static void RecieveVariableMessage(const NetMessage& message);

            static void HandleRecieve(const NetMessage& message);

            static inline std::vector<Component*> ComponentsToStartOnDemand;
        };

    public:
        class ServerHelp
        {
        public:
            static void SendVariableScene();
            static void SendComponentScene();
            static void HandleRequestedScene();

            static void HandleRecieve(const NetMessage& aMessage);
        };
    };
}