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
        Component *component = new T();
        component->SetComponentID();
        component->gameObject = aGOID;

        myComponents.emplace_back(component);
        size_t componentCount = myComponents.size() - 1;

        auto &typeID = typeid(T);
        myEntityIDToVectorOfComponentIDs[aGOID][typeID] = componentCount;

        return static_cast<T *>(component);
    }
}