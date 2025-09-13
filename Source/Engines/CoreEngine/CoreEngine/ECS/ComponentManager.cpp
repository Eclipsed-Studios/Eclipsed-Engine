#include "ComponentManager.h"

namespace Eclipse
{
    void ComponentManager::Init()
    {
        myComponentData = new uint8_t[MAX_COMPONENT_MEMORY_BYTES];
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

    GameObject* ComponentManager::CreateGameObject()
    {
        GameObject* obj = new GameObject(myNextGameobjectID);
        myEntityIdToEntity[myNextGameobjectID] = obj;

        obj->AddComponent<Transform2D>();

        myNextGameobjectID++;
        return obj;
    }

    GameObject* ComponentManager::CreateGameObjectNoTransform()
    {
        GameObject* obj = new GameObject(myNextGameobjectID);
        myEntityIdToEntity[myNextGameobjectID] = obj;

        myNextGameobjectID++;
        return obj;
    }

    void ComponentManager::BeginCollisions(GameObjectID aGOID)
    {
        auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

        for (auto& component : components)
            for (auto& [_, componentIndex] : components)
                myComponents[componentIndex]->OnCollisionEnter();
    }
    void ComponentManager::EndCollisions(GameObjectID aGOID)
    {
        auto& components = myEntityIDToVectorOfComponentIDs.at(aGOID);

        for (auto& component : components)
            for (auto& [_, componentIndex] : components)
                myComponents[componentIndex]->OnCollisionExit();
    }
}