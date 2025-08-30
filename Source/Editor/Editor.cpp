#include "Editor.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "TemporarySettingsSingleton.h"

#include <stdio.h>

#include "Sprite.h"
#include "AssetManagement/Resources/Shaders/Shader.h"
#include "AssetManagement/Resources.h"

#include "CoreEngine/Components/SpriteRendrer2D.h"


#define GLFW_EXPOSE_NATIVE_WIN32

#include "ImGui/ImGui/imgui.h"
#include "ImGui/ImGui/imgui_impl_glfw.h"
#include "ImGui/ImGui/imgui_impl_opengl3.h"


void WindowChangeDimenstions(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    ENGINE_NAMESPACE::TemporarySettingsSingleton::Get().SetResolution(width, height);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

namespace ENGINE_NAMESPACE
{
    ErrorCode Editor::Init()
    {
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


        // Pls move engine :)
        componentManager.AddComponent<SpriteRendrer2D>(1);

        componentManager.AwakeComponents();
        componentManager.StartComponents();


        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            ImGuiIO& io = ImGui::GetIO();
            io.IniFilename = NULL;

            //ImGui::LoadIniSettingsFromDisk(IMGUISETTINGSDIR);

            // Setup Platform/Renderer bindings
            ImGui_ImplGlfw_InitForOpenGL(myWindow, true);
            ImGui_ImplOpenGL3_Init("#version 460");
        }


        return ErrorCode::SUCCESS;
    }

    void Editor::Begin()
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        componentManager.EarlyUpdateComponents();
    }

    void Editor::Update()
    {
        ImGui::Begin("HEJSAN");
        ImGui::End();


        componentManager.UpdateComponents();
    }

    void Editor::Render()
    {
        componentManager.LateUpdateComponents();
    }

    void Editor::End()
    {
        glfwSwapBuffers(myWindow);
    }
}