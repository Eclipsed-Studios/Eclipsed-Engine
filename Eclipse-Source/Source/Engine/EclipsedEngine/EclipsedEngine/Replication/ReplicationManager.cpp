//#include "ReplicationManager.h"
//
//#include "ReplicatedVariable.h"
//
//#include "Utilities/Common/Timer.h"
//#include "Utilities/Common/MainSingleton.h"
//
//#include "NetworkEngine/Client/Client.h"
//#include "NetworkEngine/Server/Server.h"
//
//#include <iostream>
//
//namespace Eclipse::Replication
//{
//    void ReplicationManager::ReplicatedOnPlay()
//    {
//        for (auto& ReplicationVariable : PossibleReplicatedVariableList)
//        {
//            if (ReplicationVariable.second->ConnectedComponent->IsReplicated)
//                RealReplicatedVariableList.emplace(ReplicationVariable);
//        }
//    }
//
//    void ReplicationManager::ReplicateVariable(unsigned aID)
//    {
//        RealReplicatedVariableList.at(aID)->ReplicateThis(aID);
//    }
//
//    void ReplicationManager::CreateServer()
//    {
//        server = &Utilities::MainSingleton::RegisterInstance<Server>(ioContext);
//    }
//    void ReplicationManager::CreateClient()
//    {
//        const char* ip = "127.0.0.1";
//        client = &Utilities::MainSingleton::RegisterInstance<Client>(ioContext, ip);
//
//        NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_Connect, &ip, 1, true);
//
//        client->Send(message, [ip]() {
//
//            NetMessage message = NetMessage::BuildGameObjectMessage(1, MessageType::Msg_RequestSceneInfo, &ip, 1, true);
//
//            client->Send(message);
//            });
//    }
//
//    void ReplicationManager::Start()
//    {
//        if (startedGame)
//            return;
//
//        if (startServer)
//            CreateServer();
//
//        if (startClient)
//            CreateClient();
//
//        ReplicatedOnPlay();
//
//        ReplicatedVariabpePtr = &RealReplicatedVariableList;
//
//        startedGame = true;
//    }
//
//    void ReplicationManager::Update()
//    {
//        if (client)
//            client->Update();
//        if (server)
//            server->Update();
//
//        static float timer = 0.f;
//        timer -= Time::GetDeltaTime();
//
//        if (timer <= 0)
//        {
//            for (auto& ReplicationVariable : RealReplicatedVariableList)
//            {
//                if (!ReplicationVariable.second->ManualVariableSending)
//                    ReplicationVariable.second->ReplicateThis(ReplicationVariable.first);
//            }
//
//            timer = 0.005f;
//        }
//    }
//
//    void ReplicationManager::CreateComponentMessage(Component* aComponent, NetMessage& outMessage)
//    {
//        char Data[512];
//        
//        const char* ComponentName = aComponent->GetComponentName();
//        
//        int LengthOfComponentName = strlen(ComponentName);
//        
//        memcpy(Data, &aComponent->myInstanceComponentID, sizeof(int));
//        memcpy(Data + sizeof(int), &LengthOfComponentName, sizeof(int));
//        memcpy(Data + sizeof(int) + sizeof(int), ComponentName, LengthOfComponentName);
//
//        int DataAmount = LengthOfComponentName + sizeof(int) + sizeof(int);
//
//        outMessage = NetMessage::BuildGameObjectMessage(aComponent->gameObject->GetID(), MessageType::Msg_AddComponent, Data, DataAmount, true);
//    }
//}