#include "ComponentManager.h"

namespace Eclipse
{
    void ComponentManager::Init()
    {
        myComponentData = static_cast<char*>(malloc(MAX_COMPONENT_MEMORY_BYTES));
    }

    void ComponentManager::AwakeComponents()
    {
        for (auto& component : myComponents)
            component->Awake();
    }
    void ComponentManager::StartComponents()
    {
        for (auto& component : myComponents)
            component->Start();
    }

    void ComponentManager::EarlyUpdateComponents()
    {
        for (auto& component : myComponents)
            component->EarlyUpdate();
    }
    void ComponentManager::UpdateComponents()
    {
        for (auto& component : myComponents)
            component->Update();
    }
    void ComponentManager::LateUpdateComponents()
    {
        for (auto& component : myComponents)
            component->OnDrawGizmos();

        for (auto& component : myComponents)
            component->LateUpdate();
    }
    const std::vector<Component*>& ComponentManager::GetComponents()
    {
        return myComponents;
    }

    void ComponentManager::BeginCollisions(GameObject aGOID)
    {
        auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

        for (auto& component : components)
            for (auto& [_, componentIndex] : components)
                myComponents[componentIndex]->OnCollisionEnter();
    }
    void ComponentManager::EndCollisions(GameObject aGOID)
    {
        auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

        for (auto& component : components)
            for (auto& [_, componentIndex] : components)
                myComponents[componentIndex]->OnCollisionExit();
    }
}