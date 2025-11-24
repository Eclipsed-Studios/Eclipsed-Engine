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
            int vectorIndex = 0;
            int dataAmount = 0;

            size_t offset = 0;

            memcpy(&vectorIndex, message.data + offset, sizeof(vectorIndex));
            offset += sizeof(vectorIndex);

            memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
            offset += sizeof(dataAmount);

            auto& Variable = Replication::ReplicationManager::ReplicatedVariableList[vectorIndex];

            void* variableData = Variable->myVariableAddress;

            memcpy(variableData, message.data + offset, dataAmount);
            offset += dataAmount;
        }
        break;
        }
    }
}