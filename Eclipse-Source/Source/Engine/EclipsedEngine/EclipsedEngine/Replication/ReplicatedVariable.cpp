#include "ReplicatedVariable.h"

namespace Eclipse::Replication
{
    void BaseReplicatedVariable::ReplicateThis(unsigned aID)
    {
        if (!ConnectedComponent->IsOwner())
            return;


        char* data = new char[sizeof(aID) + sizeof(dataAmount) + dataAmount];

        size_t offset = 0;

        memcpy(data + offset, &aID, sizeof(aID));
        offset += sizeof(aID);

        memcpy(data + offset, &dataAmount, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        memcpy(data + offset, myVariableAddress, dataAmount);
        offset += dataAmount;

        NetMessage message = NetMessage::BuildGameObjectMessage(ConnectedComponent->gameObject->GetID(), MessageType::Msg_Variable, data, offset, false);

        if (Eclipse::MainSingleton::Exists<Server>())
        {
            Server& server = Eclipse::MainSingleton::GetInstance<Server>();
            server.Send(message);
            return;
        }
        else if (Eclipse::MainSingleton::Exists<Client>())
        {
            Client& client = Eclipse::MainSingleton::GetInstance<Client>();
            client.Send(message);
            return;
        }

    }
}