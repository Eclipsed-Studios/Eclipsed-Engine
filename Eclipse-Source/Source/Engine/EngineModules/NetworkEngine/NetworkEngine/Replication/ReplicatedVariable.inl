#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

#include "Utilities/Reflection/Reflection.h"

#include "utilities/Common/MainSingleton.h"

#include "EntityEngine/Components/Base/Component.h"

#include "NetworkEngine/Client/Client.h"

namespace Eclipse::Replication
{
    ReplicatedVariable::ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic)
    {
        bool variableExist = false;

        auto& reflectionList = Reflection::ReflectionManager::GetList();
        auto& variableList = reflectionList.at(aComponent);

        for (auto& variable : variableList)
        {
            if (variable->GetName() == aName)
            {
                myVariableAddress = variable->GetData();
                dataAmount = variable->GetSizeInBytes();
                variableExist = true;
                break;
            }
        }

        assert(variableExist);

        vectorIndex = ReplicationManager::ReplicatedVariableList.size();
        ReplicationManager::ReplicatedVariableList.emplace_back(this);
    }

    void ReplicatedVariable::ReplicateThis()
    {
        char* data = new char[sizeof(vectorIndex) + sizeof(int) + dataAmount];

        size_t offset = 0;

        memcpy(data + offset, &vectorIndex, sizeof(vectorIndex));
        offset += sizeof(vectorIndex);

        memcpy(data + offset, &dataAmount, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        memcpy(data + offset, myVariableAddress, dataAmount);
        offset += dataAmount;

        NetMessage message = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_Variable, data, dataAmount, false);

        Client& client = Utilities::MainSingleton::GetInstance<Client>();
        client.Send(message, true);
    }
}