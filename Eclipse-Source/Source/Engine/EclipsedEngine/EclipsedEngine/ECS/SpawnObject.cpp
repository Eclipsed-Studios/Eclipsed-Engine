#include "SpawnObject.h"

#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

#include "EntityEngine/GameObject.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EclipsedEngine/Reflection/Reflection.h"
#include "EclipsedEngine/Scenes/SceneLoader.h"

namespace Eclipse
{
    void InternalSpawnObjectClass::StartChildren(std::vector<GameObject*>& aChildComponents)
    {
        for (auto& child : aChildComponents)
        {
            if (child->GetChildCount() > 0)
                StartChildren(child->GetChildren());

            for (auto& component : ComponentManager::GetComponents(child->GetID()))
                component->OnSceneLoaded();

            for (auto& component : ComponentManager::GetComponents(child->GetID()))
            {
                component->OnComponentAdded();
                //component->ComponentCreated();
            }
        }
    }

    void InternalSpawnObjectClass::PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator)
    {
        aGameObject = ComponentManager::CreateGameObject();
        aGameObject->SetName(gameobject["Name"].GetString());

        for (auto& components : gameobject["Components"].GetArray())
        {
            for (auto coIt = components.MemberBegin(); coIt != components.MemberEnd(); coIt++)
            {
                Component* component;
                component = ComponentRegistry::GetAddComponent(coIt->name.GetString())(*aGameObject, Component::GetNextComponentID());

                auto& reflectedList = Reflection::ReflectionManager::GetList();
                if (reflectedList.find(component) == reflectedList.end())
                    continue;

                auto& reflectedVars = reflectedList.at(component);

                int refIndex = 0;

                for (auto varIt = coIt->value.MemberBegin(); varIt != coIt->value.MemberEnd(); varIt++)
                {
                    auto& reflectedVariable = reflectedVars.at(refIndex++);
                    SceneLoader::LoadType(reflectedVariable, coIt->value);
                }

                if(coIt->value.HasMember("IsReplicated"))
                    component->IsReplicated = coIt->value["IsReplicated"].GetBool();
            }
        }

        if (gameobject.HasMember("Children"))
        {
            auto childArray = gameobject["Children"].GetArray();
            for (auto& child : childArray)
            {
                GameObject* newGameObject;
                PasteGameObject(newGameObject, child, anAllocator);

                aGameObject->AddChild(newGameObject);
                newGameObject->SetParent(aGameObject);
            }
        }
    }


    GameObject* InternalSpawnObjectClass::CreateObjectFromJsonString(const char* aData)
    {
        rapidjson::Document d;
        d.SetObject();
        rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

        if (d.Parse(aData).HasParseError())
            return nullptr;

        if (!d.IsObject())
            return nullptr;

        if (!d.HasMember("CopyType"))
            return nullptr;
        if (d["CopyType"].GetInt() != 1)
            return nullptr;

        for (auto& gameobject : d["Gameobjects"].GetArray())
        {
            GameObject* newGameobject;
            PasteGameObject(newGameobject, gameobject, jsonAllocator);

            if (newGameobject->GetChildCount() > 0)
                StartChildren(newGameobject->GetChildren());

            auto components = ComponentManager::GetComponents(newGameobject->GetID());

            std::sort(components.begin(), components.end(), [&](Component* aComp0, Component* aComp1)
                {
                    return aComp0->GetUpdatePriority() > aComp1->GetUpdatePriority();
                });

            for (auto& component : components)
                component->OnComponentAdded();

            for (auto& component : components)
                component->OnSceneLoaded();

            return newGameobject;
        }

        return nullptr;
    }
}