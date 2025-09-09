#include "Editor.h"

#include "MainSingleton.h"

#include "Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "PlatformIntegration/DiscordIntegration.h"

#include "SettingsManager.h"

#include "Files/MetaFileRegistry.h"

#include "defines.h"

#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include <rapidjson/rapidjson/stringbuffer.h>
#include <rapidjson/rapidjson/prettywriter.h>

namespace ENGINE_NAMESPACE::Editor
{
    ErrorCode EditorContext::Init()
    {
        MetaFileRegistry::Load();

        PlatformIntegration::Discord::SetupWithID(1401121853829025922);
        PlatformIntegration::Discord::SetLargeImage("noah1");

        Engine::Init();

        myWindow = Utilities::MainSingleton::GetInstance<GLFWwindow*>();

        ImGui_Impl::ImplementImGui(myWindow);

        myWindowManager.Begin();

        return ErrorCode::SUCCESS;
    }

    bool EditorContext::BeginFrame()
    {
        bool beginRet = Engine::BeginFrame();
        ImGui_Impl::NewFrame();
        return beginRet;
    }

    void SaveLayerEditToJSON()
    {
        std::string filePath = ASSET_PATH"CollisionLayers.json";
        rapidjson::Document document;
        document.SetObject();

        auto allocator = document.GetAllocator();

        rapidjson::Value layers(rapidjson::kArrayType);

        for (int layer : PhysicsEngine::myCollisionLayers)
            layers.PushBack(layer, allocator);

        document.AddMember("Layer", layers, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::ofstream ofs(filePath);
        ofs << buffer.GetString();
        ofs.close();
    }

    void DrawLayerEdit()
    {
        ImGui::Begin("Layers");

        int collisionLayerCount = layerCount;

        ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_HighlightHoveredColumn | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit;

        int columnCount = collisionLayerCount + 2;
        if (ImGui::BeginTable("CollisionLayers", columnCount, tableFlags))
        {
            ImGui::TableSetupColumn("Layers", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
            for (int n = 1; n < columnCount - 1; n++)
            {
                ImGui::TableSetupColumn(GetCollisionLayerAsName(static_cast<Layer>(1 << n)).c_str(), columnFlags);
            }

            ImGui::PushID(7834768345);
            ImGui::TableAngledHeadersRow();
            ImGui::PopID();

            ImGui::PushID(78347688345);
            ImGui::TableHeadersRow();
            ImGui::PopID();

            int totalID = 0;
            for (int i = 0; i < collisionLayerCount; ++i)
            {
                totalID++;
                std::string collisionName = GetCollisionLayerAsName(static_cast<Layer>(1 << i));

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", collisionName.c_str());

                for (int j = 0; j < collisionLayerCount - i; j++)
                {
                    ImGui::TableNextColumn();

                    totalID++;
                    int hasLayer = PhysicsEngine::myCollisionLayers[i] & (1 << (collisionLayerCount - 1 - j));

                    bool hasLayerBool = static_cast<bool>(hasLayer);

                    ImGui::PushID(totalID);
                    ImGui::SetNextItemWidth(10);
                    if (ImGui::Checkbox("", &hasLayerBool))
                    {
                        if (hasLayerBool)
                        {
                            PhysicsEngine::myCollisionLayers[collisionLayerCount - 1 - j] |= (1 << i);
                            PhysicsEngine::myCollisionLayers[i] |= (1 << (collisionLayerCount - 1 - j));
                        }
                        else
                        {
                            PhysicsEngine::myCollisionLayers[collisionLayerCount - 1 - j] &= ~(1 << i);
                            PhysicsEngine::myCollisionLayers[i] &= ~(1 << (collisionLayerCount - 1 - j));
                        }

                        SaveLayerEditToJSON();
                    }
                    ImGui::PopID();
                }
            }

            ImGui::EndTable();
        }

        ImGui::End();
        //ImGui::PopStyleVar();
    }

    void EditorContext::Update()
    {
        myWindowManager.Update();
        Engine::Update();

        DrawLayerEdit();

        ImGui::Begin("Test collision showing");
        ImGui::Checkbox("Draw Physics Debug Lines##DrawAnyPhysicsDebugLines", &PhysicsEngine::GetDebugDraw());
        ImGui::Checkbox("Draw Shapes##DebugDrawShapes", &PhysicsEngine::GetDebugDrawShapes(drawShapes));
        ImGui::Checkbox("Draw Queries##DebugDrawQueries", &PhysicsEngine::GetDebugDrawShapes(drawQueries));
        ImGui::Checkbox("Draw Joints##DebugDrawJoints", &PhysicsEngine::GetDebugDrawShapes(drawJoints));
        ImGui::Checkbox("Draw Joints Advanced##DebugDrawJointsAdvanced", &PhysicsEngine::GetDebugDrawShapes(drawJointExtras));
        ImGui::Checkbox("Draw Bounds##DebugDrawBounds", &PhysicsEngine::GetDebugDrawShapes(drawBounds));
        ImGui::Checkbox("Draw Mass##DebugDrawMass", &PhysicsEngine::GetDebugDrawShapes(drawMass));
        ImGui::Checkbox("Draw Body Names##DebugDrawBodyNames", &PhysicsEngine::GetDebugDrawShapes(drawBodyNames));
        ImGui::Checkbox("Draw Contacts##DebugDrawContacts", &PhysicsEngine::GetDebugDrawShapes(drawContacts));
        ImGui::Checkbox("Draw Graph Colors##DebugDrawGraphColors", &PhysicsEngine::GetDebugDrawShapes(drawGraphColors));
        ImGui::Checkbox("Draw Contact Normals##DebugDrawContactNormals", &PhysicsEngine::GetDebugDrawShapes(drawContactNormals));
        ImGui::Checkbox("Draw Contact Impulses##DebugDrawContactImpulses", &PhysicsEngine::GetDebugDrawShapes(drawContactImpulses));
        ImGui::Checkbox("Draw Contact Features##DebugDrawContactFeatures", &PhysicsEngine::GetDebugDrawShapes(drawContactFeatures));
        ImGui::Checkbox("Draw Friction Impulse##DebugDrawFrictionImpulse", &PhysicsEngine::GetDebugDrawShapes(drawFrictionImpulses));
        ImGui::Checkbox("Draw Islands##DebugDrawIslands", &PhysicsEngine::GetDebugDrawShapes(drawIslands));
        ImGui::End();
    }

    void EditorContext::Render()
    {
        ImGui_Impl::Render();
    }

    void EditorContext::EndFrame()
    {
        Engine::EndFrame();
    }

    void EditorContext::End()
    {
        MetaFileRegistry::Save();
        myWindowManager.End();
        //Utilities::BlackBoard& engineSettings = SettingsManager::GetSettings();

        //engineSettings.Add<std::string>("GameName", "Template_v.0.0.1");
        //engineSettings.Add<std::string>("GameTitle", "Template");

        //engineSettings.Add<Math::Vector2i>("Resolution", { 1280, 720 });
        //engineSettings.Add<bool>("Fullscreen", false);
        //engineSettings.Add<int>("NumberOfRenderBuffer", 0);


        SettingsManager::Save();
    }
}