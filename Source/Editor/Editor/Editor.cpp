#include "Editor.h"

#include "MainSingleton.h"

#include "Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "PlatformIntegration/DiscordIntegration.h"

#include "SettingsManager.h"

#include "Files/MetaFileRegistry.h"

#include "defines.h"


#include "PhysicsEngine.h"

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

    void EditorContext::Update()
    {
        myWindowManager.Update();
        Engine::Update();

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