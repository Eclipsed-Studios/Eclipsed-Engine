#include "Replication.h"

#include "NetworkEngine/Shared/Message.h"

#include "NetworkEngine/Server/Server.h"
#include "NetworkEngine/Client/Client.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"
#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Replication/ReplicationManager.h"
#include "EclipsedEngine/Replication/ReplicatedVariable.h"

#include <iostream>

namespace Eclipse::Replication
{
    void ReplicationHelper::ClientHelp::RecieveAddComponentMessage(const NetMessage& message)
    {
        // if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
        // {
        //     GameObject* gameobject = ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
        //     gameobject->SetIsOwner(true);
        // }

        int ComponentID = 0;
        memcpy(&ComponentID, message.data, sizeof(int));

        int ComponentNameCharCount = 0;
        memcpy(&ComponentNameCharCount, message.data + sizeof(int), sizeof(int));

        char NameBuffer[512];

        memcpy(NameBuffer, message.data + sizeof(int) + sizeof(int), ComponentNameCharCount);
        memset(NameBuffer + ComponentNameCharCount, '\0', 1);

        const char* name = NameBuffer;

        for (auto& component : ComponentManager::GetComponents(message.MetaData.GameObjectID))
        {
            const char* CurrentComponentName = component->GetComponentName();
            if (!memcmp(name, CurrentComponentName, strlen(name)))
                return;
        }

        std::string StringName = name;
        CommandListManager::GetHappenAtBeginCommandList().Enqueue([StringName, goid = message.MetaData.GameObjectID, ComponentID] {

            Component* newCompoennt = ComponentRegistry::GetAddComponent(StringName)(goid, ComponentID);

            newCompoennt->SetIsOwner(false);
            //ComponentsToStartOnDemand.emplace_back(newCompoennt);

            newCompoennt->OnComponentAdded();

            newCompoennt->Awake();
            newCompoennt->Start();
            });

    }

    void ReplicationHelper::ClientHelp::RecieveStartRecievedComponents(const NetMessage& message)
    {
        for (Component* component : ComponentsToStartOnDemand)
        {

        }

        ComponentsToStartOnDemand.clear();
    }

    void ReplicationHelper::ClientHelp::RecieveCreateObjectMessage(const NetMessage& message)
    {
        if (ComponentManager::HasGameObject(message.MetaData.GameObjectID))
            return;

        GameObject* gameobject = ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
        gameobject->SetIsOwner(false);
    }

    void ReplicationHelper::ClientHelp::RecieveDeleteObjectMessage(const NetMessage& message)
    {
        if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
            return;

        ComponentManager::Destroy(message.MetaData.GameObjectID);
    }

    void ReplicationHelper::ClientHelp::RecieveVariableMessage(const NetMessage& message)
    {
        unsigned replicationVarIndex = 0;
        unsigned componentID = 0;
        int dataAmount = 0;

        size_t offset = 0;

        memcpy(&componentID, message.data + offset, sizeof(componentID));
        offset += sizeof(componentID);

        memcpy(&replicationVarIndex, message.data + offset, sizeof(replicationVarIndex));
        offset += sizeof(replicationVarIndex);

        memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        auto variableIt = Replication::ReplicationManager::RealReplicatedVariableList.find(componentID);
        if (variableIt == Replication::ReplicationManager::RealReplicatedVariableList.end())
            return;

        Replication::ReplicatedVariable<Component>* Variable = reinterpret_cast<Replication::ReplicatedVariable<Component>*>(variableIt->second[replicationVarIndex]);

        Component* component = Variable->ConnectedComponent;
        const auto& ReppedFunction = Variable->OnRepFunction;

        void* variableData = Variable->myReflectVariable->GetData();
        memcpy(variableData, message.data + offset, dataAmount);
        offset += dataAmount;

        (component->*ReppedFunction)();


        /*myReflectVariable->GetData()
            // Debug recieve numbers
            static Math::Vector4f vec;
            memcpy(vec.data, Variable->myReflectVariable->GetData(), dataAmount);
            std::cout << replicationVarID << ", ";
            if (dataAmount > 0)
                std::cout << "  X: " << vec.X;
            if (dataAmount > 4)
                std::cout << "  Y: " << vec.Y;
            if (dataAmount > 8)
                std::cout << "  Z: " << vec.Z;
            if (dataAmount > 12)
                std::cout << "  W: " << vec.Z;
            std::cout << std::endl;
        */

    }

    void ReplicationHelper::ClientHelp::HandleRecieve(const NetMessage& message)
    {
        switch (message.MetaData.Type)
        {
        case MessageType::Msg_Variable:
        {
            ReplicationHelper::ClientHelp::RecieveVariableMessage(message);
        }
        break;
        case MessageType::Msg_CreateObject:
        {
            ReplicationHelper::ClientHelp::RecieveCreateObjectMessage(message);
        }
        break;
        case MessageType::Msg_SentAllObjects:
        {
            ReplicationHelper::ClientHelp::RecieveStartRecievedComponents(message);
        }
        break;
        case MessageType::Msg_DeleteObject:
        {
            ReplicationHelper::ClientHelp::RecieveDeleteObjectMessage(message);
        }
        break;
        case MessageType::Msg_AddComponent:
        {
            ReplicationHelper::ClientHelp::RecieveAddComponentMessage(message);
        }
        break;
        }
    }

    void ReplicationHelper::ServerHelp::SendVariableScene()
    {
        const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
        for (auto& Component : variableManager)
        {
            for (int i = 0; i < Component.second.size(); i++)
            {
                auto& Variable = Component.second[i];
                if (Variable->ConnectedComponent->IsReplicated)
                {
                    Variable->ReplicateThis(i, true);
                }
            }
        }
    }

    void ReplicationHelper::ServerHelp::SendComponentScene()
    {
        std::unordered_set<unsigned> ReplicatedGameObjects;

        const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
        for (auto& Variable : variableManager)
        {
            unsigned gameobjectID = Variable.second[0]->ConnectedComponent->gameObject->GetID();
            ReplicatedGameObjects.emplace(gameobjectID);
        }

        for (const auto& gameobject : ReplicatedGameObjects)
        {
            std::vector<Component*> components = ComponentManager::GetComponents(gameobject);

            for (const auto& component : components)
            {
                if (!component->IsReplicated)
                    continue;

                NetMessage message;
                Replication::ReplicationManager::CreateComponentMessage(component, message);

                static int TotalCoponentMessagesRecieved = 0;

                Server& server = Eclipse::MainSingleton::GetInstance<Server>();
                server.SendToPrev(message, [components]()
                    {
                        if (TotalCoponentMessagesRecieved++ >= components.size() - 1)
                        {
                            NetMessage msg = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_SentAllObjects, nullptr, 0, true);
                            Server& server = Eclipse::MainSingleton::GetInstance<Server>();
                            server.SendToPrev(msg, [components]()
                                {
                                    SendVariableScene();

                                    return;
                                });

                            TotalCoponentMessagesRecieved = 0;
                        }

                        return;
                    });
            }
        }
    }

    void ReplicationHelper::ServerHelp::HandleRequestedScene()
    {
        SendComponentScene();
    }

    void ReplicationHelper::ServerHelp::HandleRecieve(const NetMessage& aMessage)
    {
        switch (aMessage.MetaData.Type)
        {
        case MessageType::Msg_RequestSceneInfo:
            HandleRequestedScene();
            break;

        default:
            break;
        }
    }


}