#include "EditorActions.h"

#include "ImGui/imgui.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "EclipsedEngine/Editor/Windows/WindowTypes/HierarchyWindow.h"

#include "EclipsedEngine/Scenes/SceneManager.h"
#include "EclipsedEngine/Scenes/SceneLoader.h"
#include "EntityEngine/ComponentManager.h"
#include "CoreEngine/Clipboard.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "CoreEngine/ChatGPT_Dump/Base64.hpp"

namespace Eclipse::Editor
{
    void EditorActions::SaveScene()
    {
        SceneManager::SaveActiveScene();
    }
    void EditorActions::Save()
    {
        if (true)
        {
            SaveScene();
        }
        else if (false)
        {
            // Save active thingy like sprite editor
        }

    }

    void EditorActions::CopyGameObject(unsigned activeGO, rapidjson::Value& gameobjectJson, rapidjson::Document::AllocatorType& anAllocator)
    {
        rapidjson::Value componentArray(rapidjson::kArrayType);
        componentArray.SetArray();

        auto& reflectionList = Reflection::ReflectionManager::GetList();
        auto components = ComponentManager::GetComponents(activeGO);
        for (Component* pComp : components)
        {
            std::string compName = pComp->GetComponentName();

            if (compName == "Component")
                continue;

            rapidjson::Value component(rapidjson::kObjectType);

            rapidjson::Value componentVars(rapidjson::kObjectType);
            for (auto& var : reflectionList.at(pComp))
            {
                SceneLoader::WriteMember(componentVars, var, anAllocator);
            }
            component.AddMember(rapidjson::Value(compName.c_str(), anAllocator).Move(), componentVars, anAllocator);
            componentArray.PushBack(component, anAllocator);
        }
        gameobjectJson.AddMember("Name", rapidjson::Value(ComponentManager::myEntityIdToEntity.at(HierarchyWindow::CurrentGameObjectID)->GetName().c_str(), anAllocator), anAllocator);
        gameobjectJson.AddMember("Components", componentArray, anAllocator);

        rapidjson::Value childArray(rapidjson::kArrayType);
        childArray.SetArray();

        auto& activeGameObjectObject = ComponentManager::myEntityIdToEntity.at(activeGO);

        if (activeGameObjectObject->GetChildCount())
        {
            for (auto& child : ComponentManager::myEntityIdToEntity.at(activeGO)->GetChildren())
            {
                rapidjson::Value childObject(rapidjson::kObjectType);
                childObject.SetObject();

                CopyGameObject(child->GetID(), childObject, anAllocator);

                childArray.PushBack(childObject, anAllocator);
            }

            gameobjectJson.AddMember("Children", childArray, anAllocator);
        }
    }
    void EditorActions::CopyObject()
    {
        if (HierarchyWindow::CurrentGameObjectID <= 0)
            return;

        rapidjson::Document d;
        d.SetObject();

        rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

        d.AddMember("CopyType", 1, jsonAllocator);

        rapidjson::Value gameObjectArrayJson(rapidjson::kArrayType);
        gameObjectArrayJson.SetArray();

        rapidjson::Value gameobjectJson(rapidjson::kObjectType);
        gameobjectJson.SetObject();

        CopyGameObject(HierarchyWindow::CurrentGameObjectID, gameobjectJson, jsonAllocator);

        gameObjectArrayJson.PushBack(gameobjectJson, jsonAllocator);
        d.AddMember("Gameobjects", gameObjectArrayJson, jsonAllocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);

        const char* bufferString = buffer.GetString();
        int stringLength = strlen(bufferString);

        ClipBoard::CopyToClipboard(bufferString, stringLength);
    }

    void EditorActions::Copy()
    {
        if (true)
        {
            CopyObject();
        }
        else if (false)
        {

        }
    }

    void EditorActions::StartChildren(std::vector<GameObject*>& aChildComponents)
    {
        for (auto& child : aChildComponents)
        {
            if (child->GetChildCount() > 0)
                StartChildren(child->GetChildren());

            for (auto& component : ComponentManager::GetComponents(child->GetID()))
                component->OnSceneLoaded();

            for (auto& component : ComponentManager::GetComponents(child->GetID()))
                component->OnComponentAdded();
        }
    }
    void EditorActions::PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator)
    {
        aGameObject = ComponentManager::CreateGameObjectNoTransform();
        aGameObject->SetName(gameobject["Name"].GetString());

        for (auto& components : gameobject["Components"].GetArray())
        {
            for (auto coIt = components.MemberBegin(); coIt != components.MemberEnd(); coIt++)
            {
                Component* component;
                component = ComponentRegistry::GetAddComponent(coIt->name.GetString())(*aGameObject, Component::nextComponentID++);

                auto& reflectedList = Reflection::ReflectionManager::GetList();
                if (reflectedList.find(component) == reflectedList.end())
                    continue;

                auto& reflectedVars = reflectedList.at(component);

                int refIndex = 0;
                for (auto varIt = coIt->value.MemberBegin(); varIt != coIt->value.MemberEnd(); varIt++)
                {
                    auto& reflectedVariable = reflectedVars.at(refIndex++);
                    reflectedVariable->ResolveTypeInfo();

                    if (reflectedVariable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_String)
                    {
                        std::string strVal = varIt->value.GetString();

                        std::string* str = (std::string*)reflectedVariable->GetData();
                        str->resize(strVal.size());

                        memcpy(str->data(), strVal.data(), strVal.size());
                    }
                    else if (reflectedVariable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_List)
                    {
                        const unsigned count = varIt->value["size"].GetUint();
                        reflectedVariable->Resize(count);

                        const std::string strVal = varIt->value["data"].GetString();

                        std::vector<unsigned char> decoded = Base64::Decode(strVal);
                        memcpy(reflectedVariable->GetData(), decoded.data(), decoded.size());
                    }
                    else
                    {
                        std::string strVal = varIt->value.GetString();
                        std::vector<unsigned char> decoded = Base64::Decode(strVal);
                        memcpy(reflectedVariable->GetData(), decoded.data(), decoded.size());
                    }
                }
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
    void EditorActions::PasteObject()
    {
        char* data = (char*)ClipBoard::GetClipboardData();

        rapidjson::Document d;
        d.SetObject();
        rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

        d.Parse(data);

        if (!d.IsObject())
            return;

        if (!d.HasMember("CopyType"))
            return;
        if (d["CopyType"].GetInt() != 1)
            return;

        for (auto& gameobject : d["Gameobjects"].GetArray())
        {
            GameObject* newGameobject;
            PasteGameObject(newGameobject, gameobject, jsonAllocator);

            if (newGameobject->GetChildCount() > 0)
                StartChildren(newGameobject->GetChildren());

            for (auto& component : ComponentManager::GetComponents(newGameobject->GetID()))
                component->OnSceneLoaded();

            for (auto& component : ComponentManager::GetComponents(newGameobject->GetID()))
                component->OnComponentAdded();

            HierarchyWindow::CurrentGameObjectID = newGameobject->GetID();
        }
    }

    void EditorActions::Paste()
    {
        if (true)
        {
            PasteObject();
        }
        else if (false)
        {

        }
    }

    void EditorActions::Update()
    {
        if (ImGui::IsAnyItemActive())
            return;

        EditorActions::Action action = A_NONE;

        bool ctrl = ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl);
        if (ctrl)
        {
            bool shift = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
            if (ImGui::IsKeyPressed(ImGuiKey_S)) action = EditorActions::Action::A_Save;

            else if (ImGui::IsKeyPressed(ImGuiKey_C)) action = EditorActions::Action::A_Copy;
            else if (ImGui::IsKeyPressed(ImGuiKey_V)) action = EditorActions::Action::A_Paste;
            else if (ImGui::IsKeyPressed(ImGuiKey_D)) action = EditorActions::Action::A_Duplicate;

            else if (ImGui::IsKeyPressed(ImGuiKey_Z)) action = EditorActions::Action::A_Undo;
            else if (ImGui::IsKeyPressed(ImGuiKey_R) || (shift && ImGui::IsKeyPressed(ImGuiKey_Z))) action = EditorActions::Action::A_Redo;
        }

        ReactToAction(action);
    }

    void EditorActions::ReactToAction(EditorActions::Action anAction)
    {
        switch (anAction)
        {
        case EditorActions::Action::A_Save:
            Save();
            break;
        case EditorActions::Action::A_Copy:
            Copy();
            break;
        case EditorActions::Action::A_Paste:
            Paste();
            break;
        case EditorActions::Action::A_Duplicate:
            Copy();
            Paste();
            break;
        }
    }
}