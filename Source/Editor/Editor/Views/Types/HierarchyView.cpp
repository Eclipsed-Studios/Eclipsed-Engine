#include "HierarchyView.h"

#include "rapidjson/stringbuffer.h"
#include "ImGui/imgui.h"

#include "EclipsedEngine/ECS/ComponentManager.h"
#include "EclipsedEngine/ECS/GameObject.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
//#include "EclipsedEngine/Components/UI/RectTransform.h"
//#include "EclipsedEngine/Components/UI/TextRenderer.h"
//#include "EclipsedEngine/Components/Transform2D.h"
//#include "EclipsedEngine/Components/UI/UIImage.h"
//#include "EclipsedEngine/Components/UI/Canvas.h"
//#include "EclipsedEngine/Components/UI/Button.h"

//#include "Editor/Windows/WindowTypes/AssetWindow/AssetWindow.h"
//#include "Editor/Windows/WindowTypes/InspectorWindow.h"
#include "Editor/Common/EditorActions.h"
//#include "Editor/EditorUIManager.h"

#include "FontAwesome/7/IconsFontAwesome7.h"

#include "Editor/SelectionContext.h"

namespace Eclipse::Editor
{
    void HierarchyView::Draw()
    {
        for (const auto& [id, data] : ComponentManager::GetIDToGameObject())
        {
            if (data == nullptr) continue;
            GameObject* parent = data->GetParent();
            if (parent)
                continue;

            std::string buttonName = std::string(data->GetName() + "##" + std::to_string(id));
            const char* itemName = data->GetName().c_str();
            ImVec2 textSize = ImGui::CalcTextSize(itemName);
            bool clickedButton = ImGui::Button(buttonName.c_str(), ImVec2(textSize.x + 10, 20));

            if (clickedButton)
            {
                SelectionContext::SetActiveContext(GameObjectTarget(id));
            }
        }
    }
}