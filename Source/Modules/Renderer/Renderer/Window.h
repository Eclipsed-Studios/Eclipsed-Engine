#pragma once

#include <string>
#include "Core/Math/Vector/Vector2.h"

#define OPENGL

#ifdef OPENGL
struct GLFWwindow;
#define WINDOW_TYPE GLFWwindow
#elif DX11
//DXWindow
#elif VULKAN
//VulkanWindow
#endif

namespace Eclipse
{
	class Window
	{
    public:
        Window();
        ~Window();

        bool Init();
        void Shutdown();

        void PollEvents();
        void SwapBuffers();

        bool ShouldClose() const;

        const std::string& GetWindowTitle() const { return windowTitle; }
        void SetWindowTitle(const std::string& aTitle) { windowTitle = aTitle; }

        WINDOW_TYPE* GetNativeWindow() { return window; }
        WINDOW_TYPE* GetNativeWindow() const { return window; }

    public:
        float GetWidth() const { return windowResolution.x; }
        float GetHeight() const { return windowResolution.y; }

        Math::Vector2f GetResolution() const { return windowResolution; }
        void SetResolution(Math::Vector2f dim) { windowResolution = dim; InvokeResolutionChangeEvent(); }

    private:
        void InvokeResolutionChangeEvent();

    private:
        std::string windowTitle = "";
        Math::Vector2f windowResolution = { 1280, 720 };

        WINDOW_TYPE* window = nullptr;
	};
}