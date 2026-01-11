#include "ComponentManager.h"

#include <algorithm>
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
    inline T* ComponentManager::GetComponent(unsigned aGOID)
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
    inline T* ComponentManager::AddComponent(unsigned aGOID, bool IsReplicated)
    {
        T* component = AddComponentWithID<T>(aGOID, Component::GetNextComponentID(), IsReplicated);
        component->OnComponentAdded();

        return component;
    }

    template<typename T>
    inline T* ComponentManager::AddComponentWithID(unsigned aGOID, unsigned aComponentID, bool IsReplicated)
    {
        uint8_t* base = static_cast<uint8_t*>(myComponentData);
        uint8_t* ptrToComponent = base + myComponentMemoryTracker;
        size_t sizeOfNewComponent = sizeof(T);
        myComponentMemoryTracker += sizeOfNewComponent;

        unsigned typeIndex = GetComponentID<T>();

        if (myEntityIdToEntity.find(aGOID) == myEntityIdToEntity.end())
            myEntityIdToEntity.emplace(aGOID, CreateGameObject(aGOID));

        BeforeComponentConstruction();

        T* component = new(ptrToComponent)T();
        component->SetComponentID(aComponentID);
        component->IsReplicated = IsReplicated;

        AfterComponentConstruction();


        component->gameObject = myEntityIdToEntity.at(aGOID);
        component->myComponentComponentID = typeIndex;

        myComponentsToStartNextFrame.emplace_back(component);

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        if (IsReplicated)
        {
            CreateComponentReplicated(component);
        }

        if (myComponents.size() <= 1)
            return component;

        SortComponents();

        return component;
    }

    template <typename T>
    inline void ComponentManager::RemoveComponent(unsigned aGOID)
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

        DeleteReplicatedVariable(component->myInstanceComponentID);

        //int backComponenetIndex = myComponents.back()->myComponentIndex;
        //unsigned backGameObject = *myComponents.back()->gameObject;

        //auto& backEntityIDComponents = myEntityIDToVectorOfComponentIDs.at(backGameObject);

        //myComponents.at(componentIndex) = myComponents.back();
        //myComponents.pop_back();

        //for (auto& entity : backEntityIDComponents)
        //    if (backComponenetIndex == entity.second)
        //        backEntityIDComponents.at(entity.first) = componentIndex;
    }

}