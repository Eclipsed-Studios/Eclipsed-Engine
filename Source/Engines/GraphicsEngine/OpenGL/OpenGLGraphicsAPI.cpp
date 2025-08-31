#include "OpenGLGraphicsAPI.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <stdio.h>

#include "TemporarySettingsSingleton.h"
#include "MainSingleton.h"

namespace ENGINE_NAMESPACE
{
    void WindowChangeDimenstions(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
        ENGINE_NAMESPACE::TemporarySettingsSingleton::Get().SetResolution(width, height);
    }

    void error_callback(int error, const char *description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    // Window creation
    ErrorCode GraphicsEngine::CreateWindow()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        float x = TemporarySettingsSingleton::Get().GetResolutionX();
        float y = TemporarySettingsSingleton::Get().GetResolutionY();
        const char *gameTitle = TemporarySettingsSingleton::Get().GetGameTitle();

        myWindow = glfwCreateWindow(x, y, gameTitle, nullptr, nullptr);

        if (!myWindow)
            return ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE;

        // Set context to current context
        glfwMakeContextCurrent(myWindow);

        Utilities::MainSingleton::RegisterInstance<GLFWwindow *>() = myWindow;

        return ErrorCode::SUCCESS;
    }

    ErrorCode GraphicsEngine::InitOpenGL()
    {
        glfwSetErrorCallback(error_callback);

        int iResult;

        // GLFW initialization
        iResult = glfwInit();
        if (!iResult)
            return ErrorCode::GLFW_FAILED_TO_INITILIZE;

        ErrorCode errorCode = CreateWindow();
        if (errorCode != ErrorCode::SUCCESS)
            return errorCode;

        // Glad initialization
        {
            iResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!iResult)
                return ErrorCode::GLAD_FAILED_TO_INITILIZE;
        }

        // Setup Window size change callback
        glfwSetFramebufferSizeCallback(myWindow, WindowChangeDimenstions);

        // Extra GLFW settings
        glfwSwapInterval(TemporarySettingsSingleton::Get().GetNumRenderBuffers());

        return ErrorCode::SUCCESS;
    }

    ErrorCode GraphicsEngine::Init()
    {
        ErrorCode errorCode = InitOpenGL();

        return errorCode;
    }

    void GraphicsEngine::Update()
    {
    }
}