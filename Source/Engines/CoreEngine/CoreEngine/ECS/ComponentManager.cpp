#include "ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    void ComponentManager::AwakeComponents()
    {
        for (auto &component : myComponents)
            component->Awake();
    }
    void ComponentManager::StartComponents()
    {
        for (auto &component : myComponents)
            component->Start();
    }

    void ComponentManager::EarlyUpdateComponents()
    {
        for (auto &component : myComponents)
            component->EarlyUpdate();
    }
    void ComponentManager::UpdateComponents()
    {
        for (auto &component : myComponents)
            component->Update();
    }
    void ComponentManager::LateUpdateComponents()
    {
        for (auto &component : myComponents)
            component->LateUpdate();
    }
}