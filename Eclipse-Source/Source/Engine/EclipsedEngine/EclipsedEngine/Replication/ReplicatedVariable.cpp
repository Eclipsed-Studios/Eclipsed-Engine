#include "ReplicatedVariable.h"

namespace Eclipse::Replication
{
    void BaseReplicatedVariable::ReplicateThis(unsigned aID, bool Isgarantied)
    {
        if (!ConnectedComponent->IsOwner())
            return;

        char* data = new char[sizeof(aID) + sizeof(dataAmount) + dataAmount];

        size_t offset = 0;

        unsigned componentID = ConnectedComponent->myInstanceComponentID;
        memcpy(data + offset, &componentID, sizeof(componentID));
        offset += sizeof(componentID);

        memcpy(data + offset, &aID, sizeof(aID));
        offset += sizeof(aID);

        memcpy(data + offset, &dataAmount, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        memcpy(data + offset, myReflectVariable->GetData(), dataAmount);
        offset += dataAmount;

        NetMessage message = NetMessage::BuildGameObjectMessage(ConnectedComponent->gameObject->GetID(), MessageType::Msg_Variable, data, offset, Isgarantied);

        Client& client = Eclipse::MainSingleton::GetInstance<Client>();
        client.Send(message);
    }
}