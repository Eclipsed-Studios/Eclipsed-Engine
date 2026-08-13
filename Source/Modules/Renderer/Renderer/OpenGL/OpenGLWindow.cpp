#include "Window.h"

#include "OpenGL/glad/glad.h"
#include "OpenGL/GLFW/glfw3.h"

#include "Core/Math/Vector/Vector2.h"
#include "Core/Settings/GraphicsSettings.h"
#include "Core/Settings/EngineSettings.h"
#include "Core/ErrorCodes.h"
#include "Core/GraphicsBuffers/CameraBuffer.h"
#include "Core/MainSingleton.h"

#include "Renderer/OpenGL/OpenGLGraphicsApi.h"

namespace Eclipse
{
    Window::Window()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        Math::Vector2i resolution = Settings::GraphicsSettings::GetResolution();
        float width = resolution.x;
        float height = resolution.y;

        std::string engineName = Settings::EngineSettings::GetEngineName();
        std::string engineVersion = Settings::EngineSettings::GetEngineVersion();

        SetWindowTitle(engineName + " " + engineVersion);

        return;
    }

    Window::~Window()
    {
        Shutdown();
    }

    bool Window::Init()
    {
        window = glfwCreateWindow(windowResolution.x, windowResolution.y, windowTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);

        int x, y;
        glfwGetWindowSize(window, &x, &y);
        if (window && x == 0 && y == 0)
            return false;

        glfwMakeContextCurrent(window);

        MainSingleton::AddInstance<GLFWwindow*>(window);

        return true;
    }

    void Window::Shutdown()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        glfwTerminate();
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void Window::InvokeResolutionChangeEvent()
    {
        EventSystem::Trigger("OnChangeResolution", windowResolution);

        CameraBuffer* cameraBuffer = nullptr;
        GraphicsEngine::Get()->GetGraphicsBuffer()->GetBuffer<CameraBuffer>(cameraBuffer);

        const Math::Vector2i& resolution = Settings::GraphicsSettings::GetResolution();
        float resolutionRatio = (float)resolution.y / (float)resolution.x;
        cameraBuffer->resolutionRatio = resolutionRatio;
    }
}