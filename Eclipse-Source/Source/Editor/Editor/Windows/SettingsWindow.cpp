#include "SettingsWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include <fstream>
#include <rapidjson/rapidjson/stringbuffer.h>
#include <rapidjson/rapidjson/prettywriter.h>

namespace Eclipse::Editor
{
    void GameSettingsWindow::Update()
    {
        static bool collisionLayersShown = false;
        collisionLayersShown = ImGui::CollapsingHeader("Collision Layers");

        if (collisionLayersShown) DrawCollisionLayerEditor();
    }

    void GameSettingsWindow::DrawCollisionLayerEditor()
    {
        ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_HighlightHoveredColumn | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit;

        int columnCount = layerCount;
        if (ImGui::BeginTable("CollisionLayers", columnCount + 2, tableFlags))
        {
            // Not visible without table headersrow
            ImGui::TableSetupColumn("Layers", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
            for (int i = columnCount - 1; i >= 0; i--)
                ImGui::TableSetupColumn(Layer::AsString(Layer(1 << i)).c_str(), columnFlags);

            ImGui::PushID(7834768345);
            ImGui::TableAngledHeadersRow();
            ImGui::PopID();

            // ImGui::PushID(78347688345);
            // ImGui::TableHeadersRow();
            // ImGui::PopID();

            int totalID = 0;
            for (int i = 0; i < columnCount; ++i)
            {
                totalID++;
                std::string collisionName = Layer::AsString(Layer(1 << i));

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", collisionName.c_str());

                for (int j = 0; j < columnCount - i; j++)
                {
                    ImGui::TableNextColumn();

                    totalID++;

                    uint64_t firstLayer = PhysicsEngine::myCollisionLayers[i];
                    int secondLayer = (1 << (layerCount - 1 - j));

                    int hasLayer = firstLayer & secondLayer;

                    bool hasLayerBool = static_cast<bool>(hasLayer);

                    ImGui::PushID(totalID);
                    ImGui::SetNextItemWidth(10);
                    if (ImGui::Checkbox("", &hasLayerBool))
                    {
                        if (hasLayerBool)
                        {
                            PhysicsEngine::myCollisionLayers[layerCount - 1 - j] |= (1 << i);
                            PhysicsEngine::myCollisionLayers[i] |= (1 << (layerCount - 1 - j));
                        }
                        else
                        {
                            PhysicsEngine::myCollisionLayers[layerCount - 1 - j] &= ~(1 << i);
                            PhysicsEngine::myCollisionLayers[i] &= ~(1 << (layerCount - 1 - j));
                        }

                        SaveLayerEditToJSON();
                    }
                    ImGui::PopID();
                }
            }

            ImGui::EndTable();
        }
    }

    void GameSettingsWindow::SaveLayerEditToJSON()
    {
        std::string filePath = ASSET_PATH "CollisionLayers.json";
        rapidjson::Document document;
        document.SetObject();
        auto& allocator = document.GetAllocator();

        rapidjson::Value layersArray(rapidjson::kArrayType);
        for (int i = 0; i < layerCount; i++) {
            layersArray.PushBack(PhysicsEngine::myCollisionLayers[i], allocator);
        }

        document.AddMember("Layers", layersArray, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::ofstream ofs(filePath);
        ofs << buffer.GetString();
        ofs.close();
    }
}