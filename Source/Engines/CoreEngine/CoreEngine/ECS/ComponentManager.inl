#include "ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    template <typename T>
    inline T *ComponentManager::GetComponent(GameObject aGOID)
    {
        assert(myEntityIDToVectorOfComponentIDs.find(aGOID) != myEntityIDToVectorOfComponentIDs.end());

        auto &typeID = typeid(T);
        auto &entityIDComponents = myEntityIDToVectorOfComponentIDs.at(aGOID);
        assert(entityIDComponents.find(typeID) != entityIDComponents.end());

        int componentIndex = entityIDComponents.at(typeID);
        Component *component = myComponents.at(componentIndex);

        return static_cast<T *>(component);
    }

    template <typename T>
    inline T *ComponentManager::AddComponent(GameObject aGOID)
    {
        Component *component = new T();
        component->SetComponentID();

        myComponents.emplace_back(component);
        size_t componentCount = myComponents.size() - 1;

        auto &typeID = typeid(T);
        myEntityIDToVectorOfComponentIDs[aGOID][typeID] = componentCount;

        return static_cast<T *>(component);
    }
}