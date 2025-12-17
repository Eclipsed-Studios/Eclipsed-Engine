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
    inline T* ComponentManager::AddComponent(unsigned aGOID)
    {
        T* component = AddComponentWithID<T>(aGOID, Component::GetNextComponentID());
        component->OnComponentAdded();

        return component;
    }

    template<typename T>
    inline T* ComponentManager::AddComponentWithID(unsigned aGOID, unsigned aComponentID)
    {
        uint8_t* base = static_cast<uint8_t*>(myComponentData);
        uint8_t* ptrToComponent = base + myComponentMemoryTracker;
        size_t sizeOfNewComponent = sizeof(T);
        myComponentMemoryTracker += sizeOfNewComponent;

        unsigned typeIndex = GetComponentID<T>();

        T* component = new(ptrToComponent)T();
        component->SetComponentID(aComponentID);
        component->gameObject = myEntityIdToEntity[aGOID];
        component->myComponentComponentID = typeIndex;

        myComponentsToStart.emplace_back(component);

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        //if (Utilities::MainSingleton::Exists<Client>())
        //{
        //    NetMessage message;
        //    Replication::ReplicationManager::CreateComponentMessage(component, message);

        //    Utilities::MainSingleton::GetInstance<Client>().Send(message);
        //}

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