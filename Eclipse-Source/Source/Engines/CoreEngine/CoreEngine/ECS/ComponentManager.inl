#include "ComponentManager.h"

#include <algorithm>

#include "DebugLogger.h"
namespace Eclipse
{
    inline unsigned GetUniqueComponentTypeId()
    {
        static unsigned lastId = 0;
        return lastId++;
    }

    template <typename T>
    inline unsigned ComponentManager::GetComponentID()
    {
        static unsigned componentID = GetUniqueComponentTypeId();
        return componentID;
    }

    template <typename T>
    inline T* ComponentManager::GetComponent(GameObjectID aGOID)
    {
        if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
            return nullptr;

        unsigned typeIndex = GetComponentID<T>();

        auto& entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);

        if (entityIDComponents.find(typeIndex) == entityIDComponents.end())
            return nullptr;

        int componentIndex = entityIDComponents.at(typeIndex);
        T* component = static_cast<T*>(myComponents.at(componentIndex));

        return component;
    }

    template <typename T>
    inline T* ComponentManager::AddComponent(GameObjectID aGOID)
    {
        uint8_t* base = static_cast<uint8_t*>(myComponentData);
        uint8_t* ptrToComponent = base + myComponentMemoryTracker;
        myComponentMemoryTracker += sizeof(T);

        RegisteredTypeIndex typeIndex = GetComponentID<T>();

        if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
        {
            myEntityIdToEntity[aGOID] = CreateGameObject();
        }

        T* component = new(ptrToComponent)T();
        component->SetComponentID();
        component->gameObject = myEntityIdToEntity[aGOID];
        component->myUniqueComponentID = typeIndex;

        component->OnComponentAdded();

        myComponentsToStart.emplace_back(component);

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        if (myComponents.size() <= 1)
            return component;

        SortComponents();

        return component;
    }

    template<typename T>
    inline T* ComponentManager::AddComponentWithID(GameObjectID aGOID, unsigned aComponentID)
    {
        uint8_t* base = static_cast<uint8_t*>(myComponentData);
        uint8_t* ptrToComponent = base + myComponentMemoryTracker;
        myComponentMemoryTracker += sizeof(T);

        RegisteredTypeIndex typeIndex = GetComponentID<T>();

        if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
        {
            myEntityIdToEntity[aGOID] = CreateGameObject();
        }

        T* component = new(ptrToComponent)T();
        component->SetComponentID(aComponentID);
        component->gameObject = myEntityIdToEntity[aGOID];
        component->myUniqueComponentID = typeIndex;

        myComponentsToStart.emplace_back(component);

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        if (myComponents.size() <= 1)
            return component;

        SortComponents();

        return component;
    }

    template <typename T>
    inline void ComponentManager::RemoveComponent(GameObjectID aGOID)
    {
        if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
            return;

        unsigned typeIndex = GetComponentID<T>();

        auto& entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);

        if (entityIDComponents.find(typeIndex) == entityIDComponents.end())
            return;

        int componentIndex = entityIDComponents.at(typeIndex);
        T* component = static_cast<T*>(myComponents.at(componentIndex));
        component->OnDestroy();
        component->~T();
        entityIDComponents.erase(typeIndex);

        if (componentIndex == myComponents.size() - 1)
        {
            myComponents.pop_back();
            return;
        }

        int backComponenetIndex = myComponents.back()->myComponentIndex;
        GameObjectID backGameObject = *myComponents.back()->gameObject;

        auto& backEntityIDComponents = myEntityIDToVectorOfComponentIDs.at(backGameObject);

        myComponents.at(componentIndex) = myComponents.back();
        myComponents.pop_back();

        for (auto& entity : backEntityIDComponents)
            if (backComponenetIndex == entity.second)
                backEntityIDComponents.at(entity.first) = componentIndex;
    }

}