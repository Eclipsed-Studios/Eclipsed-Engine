#include "Client.h"

#include "NetworkEngine/Replication/ReplicatedVariable.h"
#include "NetworkEngine/Shared/Message.h"

#include <iostream>

namespace Eclipse
{
    void Client::VariableMessage(const NetMessage& message)
    {
        int replicationVarID = 0;
        int dataAmount = 0;

        size_t offset = 0;

        memcpy(&replicationVarID, message.data + offset, sizeof(replicationVarID));
        offset += sizeof(replicationVarID);

        memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        auto variableIt = Replication::ReplicationManager::ReplicatedVariableList.find(replicationVarID);
        if (variableIt == Replication::ReplicationManager::ReplicatedVariableList.end())
            return;


        // // Debug recieve numbers
        // static Math::Vector4f vec;
        // memcpy(vec.data, variableIt->second->myVariableAddress, dataAmount);
        // std::cout << replicationVarID << ", ";
        // if (dataAmount > 0)
        //     std::cout << "  X: " << vec.X;
        // if (dataAmount > 4)
        //     std::cout << "  Y: " << vec.Y;
        // if (dataAmount > 8)
        //     std::cout << "  Z: " << vec.Z;
        // if (dataAmount > 12)
        //     std::cout << "  W: " << vec.Z;

        // std::cout << std::endl;

        void* variableData = variableIt->second->myVariableAddress;
        memcpy(variableData, message.data + offset, dataAmount);

        offset += dataAmount;
    }

    void Client::HandleRecieve(const NetMessage& message)
    {
        switch (message.MetaData.Type)
        {
        case MessageType::Msg_Variable:
        {
            VariableMessage(message);
        }
        break;
        }
    }
}