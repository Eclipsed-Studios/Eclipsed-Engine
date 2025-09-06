#include "Editor.h"

#include "MainSingleton.h"

#include "Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "PlatformIntegration/DiscordIntegration.h"

#include "SettingsManager.h"

#include "Files/MetaFileRegistry.h"

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