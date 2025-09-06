#include "ComponentManager.h"

#include <algorithm>

namespace ENGINE_NAMESPACE
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
    inline T* ComponentManager::GetComponent(GameObject aGOID)
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
    inline T* ComponentManager::AddComponent(GameObject aGOID)
    {
        char* base = static_cast<char*>(myComponentData);
        char* ptrToComponent = base + myComponentMemoryTracker;
        myComponentMemoryTracker += sizeof(T);

        RegisteredTypeIndex typeIndex = GetComponentID<T>();

        T* component = new(ptrToComponent)T();
        component->SetComponentID();
        component->gameObject = aGOID;
        component->myUniqueComponentID = typeIndex;

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

myEntityIdToEntityData[aGOID] = GameObjectData();
        myEntityIDToVectorOfComponentIDs[aGOID][typeIndex] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        std::sort(myComponents.begin(), myComponents.end(), [&](Component* aComp0, Component* aComp1)
            {
                bool hasPriority = aComp0->myUpdateStartPriority > aComp1->myUpdateStartPriority;

                if (hasPriority)
                {
                    auto& mapOfComponentsGO0 = myEntityIDToVectorOfComponentIDs.at(aComp0->gameObject);
                    RegisteredTypeIndex indexComp0 = aComp0->myUniqueComponentID;
                    ComponentIndex savedValue0 = mapOfComponentsGO0.at(indexComp0);
                    
                    auto& mapOfComponentsGO1 = myEntityIDToVectorOfComponentIDs.at(aComp1->gameObject);
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

    template <typename T>
    inline void ComponentManager::RemoveComponent(GameObject aGOID)
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
        GameObject backGameObject = myComponents.back()->gameObject;

        auto& backEntityIDComponents = myEntityIDToVectorOfComponentIDs.at(backGameObject);

        myComponents.at(componentIndex) = myComponents.back();
        myComponents.pop_back();

        for (auto& entity : backEntityIDComponents)
            if (backComponenetIndex == entity.second)
                backEntityIDComponents.at(entity.first) = componentIndex;
    }

}