#pragma once

#include "Components/Component.h"

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <assert.h>

namespace ENGINE_NAMESPACE
{
    typedef unsigned GameObject;

    class ComponentManager
    {
    public:
        ComponentManager() = default;
        ~ComponentManager() = default;

        void AwakeComponents();
        void StartComponents();

        void EarlyUpdateComponents();
        void UpdateComponents();
        void LateUpdateComponents();

        template <typename T>
        T *GetComponent(GameObject aGOID);

        template <typename T>
        T *AddComponent(GameObject aGOID);

    private:
        std::vector<Component *> myComponents;

        // Gameobject to components
        std::unordered_map<GameObject, std::unordered_map<std::type_index, unsigned>> myEntityIDToVectorOfComponentIDs;
    };
}
    
#include "ComponentManager.inl"