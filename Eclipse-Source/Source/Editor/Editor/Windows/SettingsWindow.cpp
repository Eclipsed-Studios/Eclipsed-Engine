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
        int collisionLayerCount = layerCount;

        ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_HighlightHoveredColumn | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit;

        int columnCount = collisionLayerCount + 1;
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
                    int hasLayer = myCollisionLayers[i] & (1 << (collisionLayerCount - 1 - j));

                    bool hasLayerBool = static_cast<bool>(hasLayer);

                    ImGui::PushID(totalID);
                    ImGui::SetNextItemWidth(10);
                    if (ImGui::Checkbox("", &hasLayerBool))
                    {
                        if (hasLayerBool)
                        {
                            myCollisionLayers[collisionLayerCount - 1 - j] |= (1 << i);
                            myCollisionLayers[i] |= (1 << (collisionLayerCount - 1 - j));
                        }
                        else
                        {
                            myCollisionLayers[collisionLayerCount - 1 - j] &= ~(1 << i);
                            myCollisionLayers[i] &= ~(1 << (collisionLayerCount - 1 - j));
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
        std::string filePath = ASSET_PATH"CollisionLayers.json";
        rapidjson::Document document;
        document.SetObject();

        auto allocator = document.GetAllocator();

        rapidjson::Value layers(rapidjson::kArrayType);

        for (int layer : myCollisionLayers)
            layers.PushBack(layer, allocator);

        document.AddMember("Layer", layers, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::ofstream ofs(filePath);
        ofs << buffer.GetString();
        ofs.close();
    }
}