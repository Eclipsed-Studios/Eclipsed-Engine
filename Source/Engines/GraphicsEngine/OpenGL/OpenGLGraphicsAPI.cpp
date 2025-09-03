#include "OpenGLGraphicsAPI.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <stdio.h>

#include "TemporarySettingsSingleton.h"
#include "MainSingleton.h"

#include <iostream>



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

    void EnableOpenGLSettings()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ErrorCode GraphicsEngine::Init()
    {
        ErrorCode errorCode = InitOpenGL();
        EnableOpenGLSettings();
        return errorCode;
    }

    void GraphicsEngine::Begin()
    {
        glfwMakeContextCurrent(myWindow);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.4314f, 0.1804f, 0.6f, 1.0f);
    }
    void GraphicsEngine::Render()
    {
    }
    void GraphicsEngine::End()
    {
        glfwSwapBuffers(myWindow);
    }

    int GraphicsEngine::ShouldWindowClose()
    {
        return glfwWindowShouldClose(Utilities::MainSingleton::GetInstance<GLFWwindow*>());
    }

    ErrorCode GraphicsEngine::CheckErrorCodes(ErrorCode aErrorCode)
    {
        switch (aErrorCode)
        {
        case ErrorCode::GLFW_FAILED_TO_INITILIZE:
        {
            std::cout << "GLFW failed to initilize" << std::endl;
            glfwTerminate();
            return ErrorCode::FAILED;
        }
        break;
        case ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE:
        {
            std::cout << "GLFW window was not able to be created" << std::endl;
            glfwTerminate();
            return ErrorCode::FAILED;
        }
        break;
        case ErrorCode::GLAD_FAILED_TO_INITILIZE:
        {
            std::cout << "GLAD failed to initilize" << std::endl;
            glfwTerminate();
            return ErrorCode::FAILED;
        }
        break;
        }

        return ErrorCode::SUCCESS;
    }
}