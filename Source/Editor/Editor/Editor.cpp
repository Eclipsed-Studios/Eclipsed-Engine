#include "Editor.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "TemporarySettingsSingleton.h"
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

    void EditorContext::Begin()
    {
        glfwMakeContextCurrent(myWindow);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void EditorContext::Update()
    {
        ImGui_Impl::NewFrame();

        myWindowManager.Update();
        Engine::Update();
    }

    void EditorContext::Render()
    {
        ImGui_Impl::Render();
    }

    void EditorContext::End()
    {
        glfwSwapBuffers(myWindow);
    }
}