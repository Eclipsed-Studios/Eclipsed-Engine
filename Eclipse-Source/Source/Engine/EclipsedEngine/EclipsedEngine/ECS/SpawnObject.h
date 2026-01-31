#pragma once

#include "EntityEngine/GameObject.h"
#include "AssetEngine/Assets/Prefab.h"

#include "AssetEngine/Models/AssetDatas/Handles/PrefabHandle.h"

#include <vector>
#include "rapidjson/document.h"

#include "Replication/ReplicationManager.h"

#include "CoreEngine/MainSingleton.h"
#include "NetworkEngine/Client/Client.h"

#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
    class ECLIPSED_API InternalSpawnObjectClass
    {
    public:
        static GameObject* CreateObjectFromJsonString(const char* aData);

    private:
        static void StartChildren(std::vector<GameObject*>& aChildComponents);
        static void PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator);
    };


    ECLIPSED_API inline GameObject*& Instantiate(Prefab& aPrefab, bool Replicated = false)
    {
        GameObject* gameobject = InternalSpawnObjectClass::CreateObjectFromJsonString(aPrefab.GetHandle()->data);

        if (Replicated)
        {
            if (MainSingleton::Exists<Client>())
            {
                unsigned componentCount = 4;
                NetMessage msg = NetMessage::BuildGameObjectMessage(0, MessageType::Msg_SendMultipleComponents, &componentCount, sizeof(unsigned), true);
                MainSingleton::GetInstance<Client>().Send(msg);

                std::vector<unsigned> componentIDs;
                std::vector<Component*> components = gameobject->GetComponents();

                for (auto& component : components)
                {
                    NetMessage message;
                    Replication::ReplicationManager::CreateComponentMessage(component, message);
                    MainSingleton::GetInstance<Client>().Send(message);
                    //componentIDs.emplace_back(component->myInstanceComponentID);
                }

                // NetMessage message;

                // Replication::ReplicationManager::CreatePrefabMessage(gameobject->GetID(), aPrefab.GetAssetID(), componentIDs, message);

                // Client& client = Eclipse::MainSingleton::GetInstance<Client>();
                // client.Send(message);
            }
        }

        aPrefab.GetHandle()->gameobject = gameobject;
        return aPrefab.GetHandle()->gameobject;
    }
}