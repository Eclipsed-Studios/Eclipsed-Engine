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

            newCompoennt->Awake();
            newCompoennt->Start();
            newCompoennt->SetIsOwner(false);

            newCompoennt->OnComponentAdded();
            });
    }

    void ReplicationHelper::ClientHelp::RecieveCreateObjectMessage(const NetMessage& message)
    {
        if (!ComponentManager::HasGameObject(message.MetaData.GameObjectID))
        {
            GameObject* gameobject = ComponentManager::CreateGameObject(message.MetaData.GameObjectID);
            gameobject->SetIsOwner(false);
        }
    }

    void ReplicationHelper::ClientHelp::RecieveVariableMessage(const NetMessage& message)
    {
        int replicationVarID = 0;
        int dataAmount = 0;

        size_t offset = 0;

        memcpy(&replicationVarID, message.data + offset, sizeof(replicationVarID));
        offset += sizeof(replicationVarID);

        memcpy(&dataAmount, message.data + offset, sizeof(dataAmount));
        offset += sizeof(dataAmount);

        auto variableIt = Replication::ReplicationManager::RealReplicatedVariableList.find(replicationVarID);
        if (variableIt == Replication::ReplicationManager::RealReplicatedVariableList.end())
            return;

        Replication::ReplicatedVariable<Component>* Variable = reinterpret_cast<Replication::ReplicatedVariable<Component>*>(variableIt->second);

        Component* component = Variable->ConnectedComponent;
        const auto& ReppedFunction = Variable->OnRepFunction;

        (component->*ReppedFunction)();

        void* variableData = Variable->myReflectVariable->GetData();
        memcpy(variableData, message.data + offset, dataAmount);

        offset += dataAmount;

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
        case MessageType::Msg_AddComponent:
        {
            ReplicationHelper::ClientHelp::RecieveAddComponentMessage(message);
        }
        break;
        }
    }



    void ReplicationHelper::ServerHelp::SendComponentScene()
    {
        std::unordered_set<unsigned> ReplicatedGameObjects;

        const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
        for (auto& Variable : variableManager)
            ReplicatedGameObjects.emplace(Variable.second->ConnectedComponent->gameObject->GetID());

        for (const auto& gameobject : ReplicatedGameObjects)
        {
            std::vector<Component*> components = ComponentManager::GetComponents(gameobject);

            for (const auto& component : components)
            {
                // if (!component->IsReplicated)
                // 	continue;
                NetMessage message;
                Replication::ReplicationManager::CreateComponentMessage(component, message);

                Server& server = Eclipse::MainSingleton::GetInstance<Server>();
                server.SendToPrev(message);
            }
        }
    }

    void ReplicationHelper::ServerHelp::HandleRequestedScene(const NetMessage& aMessage)
    {
        static int TotalRecievedGO = 0;

        std::unordered_set<unsigned> ReplicatedGameObjects;

        const auto& variableManager = Replication::ReplicationManager::RealReplicatedVariableList;
        for (auto& Variable : variableManager)
            //if (Variable.second->ConnectedComponent->IsReplicated)
            ReplicatedGameObjects.emplace(Variable.second->ConnectedComponent->gameObject->GetID());

        int Replgameobjectsize = ReplicatedGameObjects.size() - 1;

        for (const auto& gameobject : ReplicatedGameObjects)
        {
            NetMessage message;
            message = NetMessage::BuildGameObjectMessage(gameobject, MessageType::Msg_CreateObject, &message, 0, true);

            Server& server = Eclipse::MainSingleton::GetInstance<Server>();
            server.SendPrev(message, [Replgameobjectsize]() {

                if (TotalRecievedGO++ >= Replgameobjectsize)
                {
                    TotalRecievedGO = 0;
                    SendComponentScene();
                }

                });
        }
    }

    void ReplicationHelper::ServerHelp::HandleRecieve(const NetMessage& aMessage)
    {
        switch (aMessage.MetaData.Type)
        {
        case MessageType::Msg_RequestSceneInfo:
            HandleRequestedScene(aMessage);
            break;

        default:
            break;
        }
    }


}