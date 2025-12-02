#include "ReplicationManager.h"

#include "ReplicatedVariable.h"

#include "Utilities/Common/Timer.h"
#include "Utilities/Common/MainSingleton.h"

#include "NetworkEngine/Client/Client.h"
#include "NetworkEngine/Server/Server.h"

#include <iostream>

namespace Eclipse::Replication
{
    void ReplicationManager::ReplicateVariable(unsigned aID)
    {
        ReplicatedVariableList.at(aID)->ReplicateThis(aID);
    }

    void ReplicationManager::CreateServer()
    {
        server = &Utilities::MainSingleton::RegisterInstance<Server>(ioContext);
    }
    void ReplicationManager::CreateClient()
    {
        const char* ip = "127.0.0.1";
        client = &Utilities::MainSingleton::RegisterInstance<Client>(ioContext, ip);

        NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_Connect, &ip, 0, true);

        client->Send(message, [ip]() {

            NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_RequestSceneInfo, &ip, 0, true);

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

        startedGame = true;
    }

    void ReplicationManager::Update()
    {
        if (client)
            client->Update();
        if (server)
        {
            server->Update();

            static float timer = 0.f;
            timer -= Time::GetDeltaTime();

            if (timer <= 0)
            {
                for (auto& ReplicationVariable : ReplicatedVariableList)
                {
                    if (!ReplicationVariable.second->ManualVariableSending && ReplicationVariable.second->ConnectedComponent->IsReplicated)
                        ReplicationVariable.second->ReplicateThisServer(ReplicationVariable.first);
                }

                timer = 0.005f;
            }
        }
    }

    void ReplicationManager::CreateNetworkObject(unsigned aID)
    {
        char* data = new char[sizeof(aID)];

        size_t offset = 0;

        memcpy(data + offset, &aID, sizeof(aID));
        offset += sizeof(aID);

        NetMessage message = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_Variable, data, offset, false);

        Server& server = Utilities::MainSingleton::GetInstance<Server>();
        server.Send(message);
    }
}