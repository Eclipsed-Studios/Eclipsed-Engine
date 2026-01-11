#include "ReplicationManager.h"

#include "ReplicatedVariable.h"

#include "CoreEngine/Timer.h"
#include "CoreEngine/MainSingleton.h"

#include "NetworkEngine/Client/Client.h"
#include "NetworkEngine/Server/Server.h"

#include "EclipsedEngine/Replication/Replication.h"

#include <iostream>

#include <functional>

#include "EntityEngine/Component.h"

namespace Eclipse::Replication
{
    void ReplicationManager::ReplicatedOnPlay()
    {
        for (auto& ReplicatedVariableLists : PossibleReplicatedVariableList)
        {
            RealReplicatedVariableList.emplace(ReplicatedVariableLists);
        }

        ReplicatedVariabpePtr = &RealReplicatedVariableList;
    }

    void ReplicationManager::ReplicateVariable(unsigned aComponentID, unsigned aVariableID)
    {
        RealReplicatedVariableList.at(aComponentID)[aVariableID]->ReplicateThis(aComponentID);
    }

    void ReplicationManager::CreateServer()
    {
        server = &Eclipse::MainSingleton::RegisterInstance<Server>(false, ioContext, [](const NetMessage& aMessage) {Replication::ReplicationHelper::ServerHelp::HandleRecieve(aMessage);});
    }
    void ReplicationManager::CreateClient()
    {
        const char* ip = "127.0.0.1";
        client = &Eclipse::MainSingleton::RegisterInstance<Client>(false, ioContext, ip, [](const NetMessage& aMessage) {Replication::ReplicationHelper::ClientHelp::HandleRecieve(aMessage);});

        NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_Connect, &ip, 1, true);

        client->Send(message, [ip]() {

            NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_RequestSceneInfo, &ip, 1, true);

            client->Send(message);
            });
    }

    void ReplicationManager::Start()
    {
        if (startedGame)
            return;

        if (startServer)
            CreateServer();

        if (startClient)
            CreateClient();

        ReplicatedOnPlay();

        startedGame = true;
    }

    void ReplicationManager::Update()
    {
        if (client)
            client->Update();
        if (server)
            server->Update();

        static float timer = 0.f;
        timer -= Time::GetDeltaTime();

        if (timer <= 0)
        {
            for (auto& [_, ReplicationVariableList] : RealReplicatedVariableList)
            {
                for (int i = 0; i < ReplicationVariableList.size(); i++)
                {
                    auto& Variable = ReplicationVariableList[i];
                    if (!Variable->ManualVariableSending)
                        Variable->ReplicateThis(i);
                }

            }

            timer = 0.005f;
        }
    }

    // This might be stupid if one thinks about it but if you only want the object then do that
    void ReplicationManager::CreateGOMessage(int aGameobjectID, NetMessage& outMessage)
    {
        outMessage = NetMessage::BuildGameObjectMessage(aGameobjectID, MessageType::Msg_CreateObject, &aGameobjectID, 0, true);
    }

    void ReplicationManager::DeleteGOMessage(int aGameobjectID, NetMessage& outMessage)
    {
        outMessage = NetMessage::BuildGameObjectMessage(aGameobjectID, MessageType::Msg_DeleteObject, &aGameobjectID, 0, true);
    }

    void ReplicationManager::CreateComponentMessage(Component* aComponent, NetMessage& outMessage)
    {
        char Data[512];

        const char* ComponentName = aComponent->GetComponentName();

        int LengthOfComponentName = strlen(ComponentName);

        memcpy(Data, &aComponent->myInstanceComponentID, sizeof(int));
        memcpy(Data + sizeof(int), &LengthOfComponentName, sizeof(int));
        memcpy(Data + sizeof(int) + sizeof(int), ComponentName, LengthOfComponentName);

        int DataAmount = LengthOfComponentName + sizeof(int) + sizeof(int);

        outMessage = NetMessage::BuildGameObjectMessage(aComponent->gameObject->GetID(), MessageType::Msg_AddComponent, Data, DataAmount, true);
    }


    void ReplicationManager::SetBeforeReplicatedList()
    {
        BeforeReplicatedVariableList = &(*ReplicatedVariabpePtr);
        ReplicatedVariabpePtr = &TemporaryReplicatedVariableList;
    }

    void ReplicationManager::SetAfterReplicatedList()
    {
        ReplicatedVariabpePtr = &(*BeforeReplicatedVariableList);

        for (auto& [_, ReplicatedVariableList] : ReplicationManager::TemporaryReplicatedVariableList)
        {
            for (auto Var : ReplicatedVariableList)
                (*ReplicatedVariabpePtr)[Var->ConnectedComponent->myInstanceComponentID].emplace_back(Var);
        }

        ReplicationManager::TemporaryReplicatedVariableList.erase(0);

    }
}