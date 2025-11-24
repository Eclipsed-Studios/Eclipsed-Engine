#include "ReplicationManager.h"

#include "ReplicatedVariable.h"

#include "Utilities/Common/Timer.h"
#include "Utilities/Common/MainSingleton.h"

#include "NetworkEngine/Client/Client.h"
#include "NetworkEngine/Server/Server.h"

asio::io_context ioContext;

namespace Eclipse::Replication
{
    void ReplicationManager::Init()
    {
        server = new Server(ioContext);


        const char* ip = "127.0.0.1";
        client = &Utilities::MainSingleton::RegisterInstance<Client>(ioContext, ip);
    }

    void ReplicationManager::Update()
    {
        client->Update();
        server->Update();

        static float timer = 0.f;
        timer -= Time::GetDeltaTime();

        if (timer <= 0)
        {
            for (auto& ReplicationVariable : ReplicatedVariableList)
            {
                if (!ReplicationVariable->ManualVariableSending)
                    ReplicationVariable->ReplicateThis();
            }
            timer = 0.1f;
        }
    }
}