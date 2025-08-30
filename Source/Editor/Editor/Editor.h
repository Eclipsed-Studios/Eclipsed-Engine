#pragma once

#include "ErrorCodes.h"

#include "Windows/Window.h"

#include <unordered_map>
#include "WindowManager.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE::Editor
{
    class EditorContext
    {
    public:
        EditorContext(/* args */) = default;
        ~EditorContext() = default;

        ErrorCode Init();
        void Begin();
        void Update();
        void Render();
        void End();

        template<typename T>
        void OpenWindow();

    private:
        void UpdateMainMenuBar();

    private:
        GLFWwindow* myWindow;

        WindowManager myWindowManager;
    };

    template<typename T>
    inline void EditorContext::OpenWindow()
    {
    }

}