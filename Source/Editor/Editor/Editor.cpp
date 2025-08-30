#include "Editor.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "TemporarySettingsSingleton.h"

#include <stdio.h>

#include "Engine.h"

#include "ImGui/ImGui_Impl.h"

#include "DiscordIntegration.h"

void WindowChangeDimenstions(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    ENGINE_NAMESPACE::TemporarySettingsSingleton::Get().SetResolution(width, height);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

namespace ENGINE_NAMESPACE::Editor
{
    ErrorCode EditorContext::Init()
    {
        PlatformIntegration::Discord::SetupWithID(1401121853829025922);
        PlatformIntegration::Discord::SetLargeImage("noah1");

        glfwSetErrorCallback(error_callback);

        int iResult;

        // GLFW initialization
        {
            iResult = glfwInit();
            if (!iResult)
                return ErrorCode::GLFW_FAILED_TO_INITILIZE;
        }

        // Window creation
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            float x = TemporarySettingsSingleton::Get().GetResolutionX();
            float y = TemporarySettingsSingleton::Get().GetResolutionY();
            const char *gameTitle = TemporarySettingsSingleton::Get().GetGameTitle();

            myWindow = glfwCreateWindow(x, y, gameTitle, nullptr, nullptr);
            if (!myWindow)
                return ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE;

            TemporarySettingsSingleton::Get().myWindow = myWindow;
        }

        // Set context to current context
        glfwMakeContextCurrent(myWindow);

        // Glad initialization
        {
            iResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!iResult)
                return ErrorCode::GLAD_FAILED_TO_INITILIZE;
        }

        // Setup Window size change callback
        {
            glfwSetFramebufferSizeCallback(myWindow, WindowChangeDimenstions);
        }

        // Extra GLFW settings
        {
            glfwSwapInterval(TemporarySettingsSingleton::Get().GetNumRenderBuffers());
        }

        Engine::Init();

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