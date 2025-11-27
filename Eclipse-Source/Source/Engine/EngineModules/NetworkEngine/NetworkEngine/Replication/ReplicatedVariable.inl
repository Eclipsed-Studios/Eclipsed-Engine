#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

#include "Utilities/Reflection/Reflection.h"

#include "utilities/Common/MainSingleton.h"

#include "EntityEngine/Components/Base/Component.h"

#include "NetworkEngine/Client/Client.h"

namespace Eclipse::Replication
{
    ReplicatedVariable::ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID)
    {
        bool variableExist = false;

        auto& reflectionList = Reflection::ReflectionManager::GetList();
        auto& variableList = reflectionList.at(aComponent);

        for (auto& variable : variableList)
        {
            if (variable->GetName() == aName)
            {
                variable->ResolveTypeInfo();
                
                ManualVariableSending = !anAutomatic;
                myVariableAddress = variable->GetData();
                dataAmount = variable->GetSizeInBytes();
                variableExist = true;
                break;
            }
        }

        assert(variableExist);

        ReplicationManager::ReplicatedVariableList.emplace(ID, this);
    }

    void ReplicatedVariable::ReplicateThis(unsigned aID)
    {
        if (!Utilities::MainSingleton::Exists<Client>())
            return;

        char* data = new char[sizeof(aID) + sizeof(int) + dataAmount];

        size_t offset = 0;

        memcpy(data + offset, &aID, sizeof(aID));
        offset += sizeof(aID);

        memcpy(data + offset, &dataAmount, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        memcpy(data + offset, myVariableAddress, dataAmount);
        offset += dataAmount;

        NetMessage message = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_Variable, data, offset, false);

        Client& client = Utilities::MainSingleton::GetInstance<Client>();
        client.Send(message, true);
    }
}