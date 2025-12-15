#include "ReplicatedVariable.h"
#include "ReplicationManager.h"

#include "Utilities/Reflection/Reflection.h"
#include "utilities/Common/MainSingleton.h"

#include "NetworkEngine/Server/Server.h"
#include "NetworkEngine/Client/Client.h"

#include "EntityEngine/Components/Base/Component.h"
#include "EntityEngine/GameObject.h"

namespace Eclipse::Replication
{
    template<typename T>
    ReplicatedVariable<T>::ReplicatedVariable(std::string aName, Component* aComponent, bool anAutomatic, unsigned ID, void(T::* OnRepFunctionPtr)()) : OnRepFunction(OnRepFunctionPtr)
    {
        ConnectedComponent = aComponent;

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

        ReplicationManager::EmplaceReplicatedVariable(ID, this);
    }

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

        if (Utilities::MainSingleton::Exists<Server>())
        {
            Server& server = Utilities::MainSingleton::GetInstance<Server>();
            server.Send(message);
            return;
        }
        else if (Utilities::MainSingleton::Exists<Client>())
        {
            Client& client = Utilities::MainSingleton::GetInstance<Client>();
            client.Send(message);
            return;
        }

    }
}