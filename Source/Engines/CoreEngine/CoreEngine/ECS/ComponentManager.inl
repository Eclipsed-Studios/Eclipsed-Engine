#include "ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    template <typename T>
    inline T *ComponentManager::GetComponent(GameObject aGOID)
    {
        if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
            return nullptr;

        auto &typeID = typeid(T);
        auto &entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);

        if (entityIDComponents.find(typeID) == entityIDComponents.end())
            return nullptr;

        int componentIndex = entityIDComponents.at(typeID);
        Component *component = myComponents.at(componentIndex);

        return static_cast<T *>(component);
    }

    template <typename T>
    inline T *ComponentManager::AddComponent(GameObject aGOID)
    {
        char *base = static_cast<char *>(myComponentData);
        char* ptrToComponent = base + myComponentMemoryTracker;
        myComponentMemoryTracker += sizeof(T);

        T* component = new(ptrToComponent)T();
        component->SetComponentID();
        component->gameObject = aGOID;

        myComponents.emplace_back(component);
        size_t componentIndex = myComponents.size() - 1;

        auto &typeID = typeid(T);
        myEntityIDToVectorOfComponentIDs[aGOID][typeID] = componentIndex;
        myComponents.back()->myComponentIndex = componentIndex;

        return component;        
    }

    template <typename T>
    inline void ComponentManager::RemoveComponent(GameObject aGOID)
    {
        if (myEntityIDToVectorOfComponentIDs.find(aGOID) == myEntityIDToVectorOfComponentIDs.end())
            return;

        auto &typeID = typeid(T);
        auto &entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);

        if (entityIDComponents.find(typeID) == entityIDComponents.end())
            return;

        int componentIndex = entityIDComponents.at(typeID);
        T *component = static_cast<T*>(myComponents.at(componentIndex));
        component->~T();
        entityIDComponents.erase(typeID);
        
        if (componentIndex == myComponents.size() - 1)
        {
            myComponents.pop_back();
            return;
        }

        int backComponenetIndex = myComponents.back()->myComponentIndex;
        GameObject backGameObject = myComponents.back()->gameObject;

        auto &backEntityIDComponents = myEntityIDToVectorOfComponentIDs.at(backGameObject);

        myComponents.at(componentIndex) = myComponents.back();
        myComponents.pop_back();

        for (auto &entity : backEntityIDComponents)
            if (backComponenetIndex == entity.second)
                backEntityIDComponents.at(entity.first) = componentIndex;
    }
    
}