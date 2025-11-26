#include "Client.h"

#include "NetworkEngine/Replication/ReplicatedVariable.h"
#include "NetworkEngine/Shared/Message.h"

namespace Eclipse
{
    void Client::HandleRecieve(const NetMessage& message)
    {
        switch (message.MetaData.Type)
        {
        case MessageType::Msg_Variable:
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

            void* variableData = variableIt->second->myVariableAddress;
            memcpy(variableData, message.data + offset, dataAmount);

            offset += dataAmount;
        }
        break;
        }
    }
}