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
        static GameObject* CreateObjectFromJsonStringSpecifiedIds(const char* aData,
            int aGameobjectID, const std::vector<unsigned>& aComponentsID);

    private:
        static void StartChildren(std::vector<GameObject*>& aChildComponents);

        static void PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator);
        static void PasteGameObjectSpecifiedIds(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator,
            int aGameobjectID, const std::vector<unsigned>& aComponentsID);
    };

    ECLIPSED_API inline GameObject*& Instantiate(Prefab& aPrefab, bool Replicated = false)
    {
        GameObject* gameobject = InternalSpawnObjectClass::CreateObjectFromJsonString(aPrefab.GetHandle()->data);
        gameobject->prefabAssetID = aPrefab.GetAssetID();

        gameobject->IsPrefab = true;

        if (Replicated)
            Replication::ReplicationManager::SendPrefabObject(gameobject, aPrefab);

        aPrefab.GetHandle()->gameobject = gameobject;
        return aPrefab.GetHandle()->gameobject;
    }
}