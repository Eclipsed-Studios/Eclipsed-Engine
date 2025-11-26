#include "ReplicationManager.h"

#include "ReplicatedVariable.h"

#include "Utilities/Common/Timer.h"
#include "Utilities/Common/MainSingleton.h"

#include "NetworkEngine/Client/Client.h"
#include "NetworkEngine/Server/Server.h"

#include <iostream>

asio::io_context ioContext;

namespace Eclipse::Replication
{
    void ReplicationManager::ReplicateVariable(unsigned aID)
    {
        ReplicatedVariableList.at(aID)->ReplicateThis(aID);
    }

    void ReplicationManager::CreateServer()
    {
        server = new Server(ioContext);
    }
    void ReplicationManager::CreateClient()
    {
        const char* ip = "127.0.0.1";
        client = &Utilities::MainSingleton::RegisterInstance<Client>(ioContext, ip);
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
            server->Update();

        static float timer = 0.f;
        timer -= Time::GetDeltaTime();

        if (timer <= 0)
        {
            for (auto& ReplicationVariable : ReplicatedVariableList)
            {
                if (!ReplicationVariable.second->ManualVariableSending)
                    ReplicationVariable.second->ReplicateThis(ReplicationVariable.first);
            }
            timer = 0.01f;
        }
    }
}