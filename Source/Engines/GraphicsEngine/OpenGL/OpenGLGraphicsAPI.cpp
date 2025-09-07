#include "OpenGLGraphicsAPI.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <stdio.h>

#include "TemporarySettingsSingleton.h"
#include "MainSingleton.h"

#include <iostream>

#include "Math/Vector/Vector2.h"

#include "DebugDrawers/DebugDrawer.h"

namespace ENGINE_NAMESPACE
{
    void SetWindowDimenstion()
    {
        auto& settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetOneDivResolutionX();
        float resY = settings.GetOneDivResolutionY();

        Math::Vector2f oneDivRes = { resX, resY };
        GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "resolutionMultiplier", &oneDivRes);

        float resolutionRatio = settings.GetResolutionRatio();
        GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &resolutionRatio);
    }

    void WindowChangeDimenstions(GLFWwindow* window, int width, int height)
    {
        auto& settings = TemporarySettingsSingleton::Get();

        glViewport(0, 0, width, height);
        settings.SetResolution(width, height);

        SetWindowDimenstion();
    }

    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    // Window creation
    ErrorCode GraphicsEngine::CreateWindow()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        float width = TemporarySettingsSingleton::Get().GetResolutionX();
        float height = TemporarySettingsSingleton::Get().GetResolutionY();
        const char* gameTitle = TemporarySettingsSingleton::Get().GetGameTitle();

        myWindow = glfwCreateWindow(width, height, gameTitle, nullptr, nullptr);
        SetWindowDimenstion();
        
        if (!myWindow)
        return ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE;
        
        // Set context to current context
        
        glfwMakeContextCurrent(myWindow);

        Utilities::MainSingleton::RegisterInstance<GLFWwindow*>() = myWindow;

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

        DebugDrawer::Get().Init();

        return errorCode;
    }

    void GraphicsEngine::BeginFrame()
    {
        glfwMakeContextCurrent(myWindow);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.4314f, 0.1804f, 0.6f, 1.0f);
    }

    void GraphicsEngine::SetGlobalUniforms(unsigned aShaderProgram)
    {
        myUniformManager.SetGlobalUniforms(aShaderProgram);
    }

    void GraphicsEngine::Render()
    {
        DebugDrawer::Get().Render();
    }
    void GraphicsEngine::EndFrame()
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

    void GraphicsEngine::AddGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue)
    {
        switch (aType)
        {
        case UniformType::Bool: myUniformManager.AddInt(aUniformName, (int*)aValue); return;

        case UniformType::Float: myUniformManager.AddFloat(aUniformName, (float*)aValue); return;

        case UniformType::Vector2f: myUniformManager.AddVec2Float(aUniformName, (Math::Vector2f*)aValue); return;
        case UniformType::Vector3f: myUniformManager.AddVec3Float(aUniformName, (Math::Vector4f*)aValue); return;
        case UniformType::Vector4f: myUniformManager.AddVec4Float(aUniformName, (Math::Vector4f*)aValue); return;

        case UniformType::Int: myUniformManager.AddInt(aUniformName, (int*)aValue); return;

        case UniformType::Matrix2x2f: myUniformManager.AddMat2x2(aUniformName, (float*)aValue); return;
        case UniformType::Matrix3x3f: myUniformManager.AddMat3x3(aUniformName, (float*)aValue); return;
        case UniformType::Matrix4x4f: myUniformManager.AddMat4x4(aUniformName, (float*)aValue); return;
        }
    }

    void GraphicsEngine::UpdateGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue)
    {
        switch (aType)
        {
        case UniformType::Bool: myUniformManager.UpdateInt(aUniformName, (int*)aValue); return;

        case UniformType::Float: myUniformManager.UpdateFloat(aUniformName, (float*)aValue); return;

        case UniformType::Vector2f: myUniformManager.UpdateVec2Float(aUniformName, (Math::Vector2f*)aValue); return;
        case UniformType::Vector3f: myUniformManager.UpdateVec3Float(aUniformName, (Math::Vector4f*)aValue); return;
        case UniformType::Vector4f: myUniformManager.UpdateVec4Float(aUniformName, (Math::Vector4f*)aValue); return;

        case UniformType::Int: myUniformManager.UpdateInt(aUniformName, (int*)aValue); return;

        case UniformType::Matrix2x2f: myUniformManager.UpdateMat2x2(aUniformName, (float*)aValue); return;
        case UniformType::Matrix3x3f: myUniformManager.UpdateMat3x3(aUniformName, (float*)aValue); return;
        case UniformType::Matrix4x4f: myUniformManager.UpdateMat4x4(aUniformName, (float*)aValue); return;
        }
    }
}