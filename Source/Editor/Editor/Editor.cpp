#include "Editor.h"

#include "MainSingleton.h"

#include "Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "DiscordIntegration.h"

namespace ENGINE_NAMESPACE::Editor
{
    ErrorCode EditorContext::Init()
    {
        PlatformIntegration::Discord::SetupWithID(1401121853829025922);
        PlatformIntegration::Discord::SetLargeImage("noah1");

        Engine::Init();

        myWindow = Utilities::MainSingleton::GetInstance<GLFWwindow*>();
        
        ImGui_Impl::ImplementImGui(myWindow);

        return ErrorCode::SUCCESS;
    }

    bool EditorContext::Begin()
    {
        bool beginRet = Engine::Begin();
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

    void EditorContext::End()
    {
        Engine::End();
    }
}