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
    inline unsigned GetComponentID()
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
        char* base = static_cast<char*>(myComponentData);
        char* ptrToComponent = base + myComponentMemoryTracker;
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

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        if (myComponents.size() <= 1) return component;

        std::sort(myComponents.begin(), myComponents.end(), [&](Component* aComp0, Component* aComp1)
            {
                bool hasPriority = aComp0->myUpdateStartPriority > aComp1->myUpdateStartPriority;

                if (hasPriority)
                {
                    auto& mapOfComponentsGO0 = myEntityIDToVectorOfComponentIDs.at(aComp0->gameObject->GetID());
                    RegisteredTypeIndex indexComp0 = aComp0->myUniqueComponentID;
                    ComponentIndex savedValue0 = mapOfComponentsGO0.at(indexComp0);
                    
                    auto& mapOfComponentsGO1 = myEntityIDToVectorOfComponentIDs.at(aComp1->gameObject->GetID());
                    RegisteredTypeIndex indexComp1 = aComp1->myUniqueComponentID;
                    ComponentIndex savedValue1 = mapOfComponentsGO1.at(indexComp1);
                    
                    mapOfComponentsGO0.erase(indexComp0);
                    mapOfComponentsGO1.erase(indexComp1);

                    mapOfComponentsGO0[indexComp0] = savedValue1;
                    mapOfComponentsGO1[indexComp1] = savedValue0;
                }

                return hasPriority;
            });

        return component;
    }

    template<typename T>
    inline T* ComponentManager::AddComponentWithID(GameObjectID aGOID, unsigned aComponentID)
    {
        char* base = static_cast<char*>(myComponentData);
        char* ptrToComponent = base + myComponentMemoryTracker;
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

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        if (myComponents.size() <= 1) return component;

        //  TODO: Fix? - Remvoed as of now, dont seem to work when loading a scene.
        //std::sort(myComponents.begin(), myComponents.end(), [&](Component* aComp0, Component* aComp1)
        //    {
        //        bool hasPriority = aComp0->myUpdateStartPriority > aComp1->myUpdateStartPriority;

        //        if (hasPriority)
        //        {
        //            auto& mapOfComponentsGO0 = myEntityIDToVectorOfComponentIDs.at(aComp0->gameObject->GetID());
        //            RegisteredTypeIndex indexComp0 = aComp0->myUniqueComponentID;
        //            ComponentIndex savedValue0 = mapOfComponentsGO0.at(indexComp0);
        //            
        //            auto& mapOfComponentsGO1 = myEntityIDToVectorOfComponentIDs.at(aComp1->gameObject->GetID());
        //            RegisteredTypeIndex indexComp1 = aComp1->myUniqueComponentID;
        //            ComponentIndex savedValue1 = mapOfComponentsGO1.at(indexComp1);
        //            
        //            mapOfComponentsGO0.erase(indexComp0);
        //            mapOfComponentsGO1.erase(indexComp1);

        //            mapOfComponentsGO0[indexComp0] = savedValue1;
        //            mapOfComponentsGO1[indexComp1] = savedValue0;
        //        }

        //        return hasPriority;
        //    });

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