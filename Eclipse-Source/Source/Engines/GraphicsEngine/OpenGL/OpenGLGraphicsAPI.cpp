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

#include "RenderCommands/CommandList.h"

#include "stb_image/stb_image.h"

//#include <nvml.h>

#undef CreateWindow

namespace Eclipse
{


    static std::vector<std::function<void()>> resolutionChangeCallbackFunctions;

    void SetWindowDimenstion()
    {
        auto& settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetOneDivResolutionX();
        float resY = settings.GetOneDivResolutionY();

        Math::Vector2f oneDivRes = { resX, resY };
        GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "resolutionMultiplier", &oneDivRes);

        float resolutionRatio = settings.GetResolutionRatio();
        GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &resolutionRatio);

        for (auto& callBackFunc : resolutionChangeCallbackFunctions)
            callBackFunc();
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
        //nvmlInit();

        ErrorCode errorCode = InitOpenGL();
        EnableOpenGLSettings();
        DebugDrawer::Get().Init();

        myClearColor.r = 0.4314f;
        myClearColor.g = 0.1804f;
        myClearColor.b = 0.6f;
        myClearColor.a = 1.0f;

        myMouseCursors.emplace_back(glfwCreateStandardCursor(GLFW_HAND_CURSOR));

        GLFWimage cursor;

        int nrChannels = 0;
        cursor.pixels = stbi_load(ENGINE_ASSETS_PATH"GrabbyHand.png", &cursor.width, &cursor.height, &nrChannels, 0);
        myMouseCursors.emplace_back(glfwCreateCursor(&cursor, 8.f, 8.f));

        CommandListManager::InitAllCommandLists();

        return errorCode;
    }

    void GraphicsEngine::BeginFrame()
    {
        glfwMakeContextCurrent(myWindow);
        glfwPollEvents();

        DebugDrawer::Get().Begin();

        GraphicsEngine::BindFrameBuffer(0);
        GraphicsEngine::ClearCurrentSceneBuffer(0.3f, 0.3f, 0.3f, 1);
    }

    void GraphicsEngine::SetGlobalUniforms(unsigned aShaderProgram)
    {
        myUniformManager.SetGlobalUniforms(aShaderProgram);
    }

    void GraphicsEngine::Render()
    {
#ifdef _GAME
        float resX = TemporarySettingsSingleton::Get().GetResolutionX();
        float resY = TemporarySettingsSingleton::Get().GetResolutionY();

        glViewport(0, 0, resX, resY);

        float aspectRatio = resY / resX;
        GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

        int ovColor = 1;
        GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &ovColor);

        CommandListManager::ExecuteAllCommandLists();
#else
        DebugDrawer::Get().Render();
#endif
    }
    void GraphicsEngine::EndFrame()
    {
        glfwSwapBuffers(myWindow);

        CommandListManager::ResetAllCommandLists();
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

    void GraphicsEngine::GetGlobalUniform(UniformType aType, const std::string& aUniformName, void* aValue)
    {
        switch (aType)
        {
        case UniformType::Bool: myUniformManager.GetInt(aUniformName, (int*)aValue); return;

        case UniformType::Float: myUniformManager.GetFloat(aUniformName, (float*)aValue); return;

        case UniformType::Vector2f: myUniformManager.GetVec2Float(aUniformName, (Math::Vector2f*)aValue); return;
        case UniformType::Vector3f: myUniformManager.GetVec3Float(aUniformName, (Math::Vector4f*)aValue); return;
        case UniformType::Vector4f: myUniformManager.GetVec4Float(aUniformName, (Math::Vector4f*)aValue); return;

        case UniformType::Int: myUniformManager.GetInt(aUniformName, (int*)aValue); return;

        case UniformType::Matrix2x2f: myUniformManager.GetMat2x2(aUniformName, (float*)aValue); return;
        case UniformType::Matrix3x3f: myUniformManager.GetMat3x3(aUniformName, (float*)aValue); return;
        case UniformType::Matrix4x4f: myUniformManager.GetMat4x4(aUniformName, (float*)aValue); return;
        }
    }

    void GraphicsEngine::SetUniform(UniformType aType, unsigned aShaderProgram, const std::string& aUniformName, void* aValue)
    {
        switch (aType)
        {
        case UniformType::Bool: myUniformManager.SetUniformInt(aUniformName, aShaderProgram, (int*)aValue); return;

        case UniformType::Float: myUniformManager.SetUniformFloat(aUniformName, aShaderProgram, (float*)aValue); return;

        case UniformType::Vector2f: myUniformManager.SetUniformVec2Float(aUniformName, aShaderProgram, (Math::Vector2f*)aValue); return;
        case UniformType::Vector3f: myUniformManager.SetUniformVec3Float(aUniformName, aShaderProgram, (Math::Vector4f*)aValue); return;
        case UniformType::Vector4f: myUniformManager.SetUniformVec4Float(aUniformName, aShaderProgram, (Math::Vector4f*)aValue); return;

        case UniformType::Int: myUniformManager.SetUniformInt(aUniformName, aShaderProgram, (int*)aValue); return;

        case UniformType::Matrix2x2f: myUniformManager.SetUniformMat2x2(aUniformName, aShaderProgram, (float*)aValue); return;
        case UniformType::Matrix3x3f: myUniformManager.SetUniformMat3x3(aUniformName, aShaderProgram, (float*)aValue); return;
        case UniformType::Matrix4x4f: myUniformManager.SetUniformMat4x4(aUniformName, aShaderProgram, (float*)aValue); return;
        }
    }

    void GraphicsEngine::BindTexture(int aGLType, unsigned aTextureID)
    {
        glBindTexture(aGLType, aTextureID);
    }

    void GraphicsEngine::BindFrameBuffer(unsigned aFrameBuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, aFrameBuffer);
    }

    void GraphicsEngine::ClearCurrentSceneBuffer(float aClearColorR, float aClearColorG, float aClearColorB, float aClearColorA)
    {
        glClearColor(aClearColorR, aClearColorG, aClearColorB, aClearColorA);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GraphicsEngine::RegisterListenToResolutionChange(const std::function<void()>& aLambda)
    {
        resolutionChangeCallbackFunctions.emplace_back(aLambda);
    }
    Math::Vector2i GraphicsEngine::GetWindowPosition()
    {
        int xpos, ypos;
        glfwGetWindowPos(myWindow, &xpos, &ypos);
        return Math::Vector2i(xpos, ypos);
    }


    void GraphicsEngine::SetCursor(MouseCursor aCursor)
    {
        GLFWcursor* curs = myMouseCursors[static_cast<int>(aCursor)];

        glfwSetCursor(myWindow, curs);
    }

    void GraphicsEngine::ResetCursor()
    {
        glfwSetCursor(myWindow, nullptr);
    }

    Math::Vector4ui GraphicsEngine::ReadPixel(const Math::Vector2ui& aPos)
    {
        glFlush();
        glFinish();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        unsigned char data[4];
        glReadPixels(aPos.x, aPos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

        return Math::Vector4ui(data[0], data[1], data[2], data[3]);
    }

    void GraphicsEngine::SetWindowIcon(const char* aPath)
    {
        GLFWimage images[1];
        images[0].pixels = stbi_load(aPath, &images[0].width, &images[0].height, 0, 4);
        glfwSetWindowIcon(Utilities::MainSingleton::GetInstance<GLFWwindow*>(), 1, images);
        stbi_image_free(images[0].pixels);
    }
}

