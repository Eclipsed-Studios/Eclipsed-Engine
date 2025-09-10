#pragma once

#include "WindowManager.h"

#include "ErrorCodes.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE::Editor
{
    class EditorContext
    {
    public:
        EditorContext(/* args */) = default;
        ~EditorContext() = default;

        ErrorCode Init();
        bool BeginFrame();
        void Update();
        void Render();
        void EndFrame();

        void End();


        template<typename T>
        void OpenWindow();

    private:
        GLFWwindow* myWindow;

        WindowManager myWindowManager;
    };

    template<typename T>
    inline void EditorContext::OpenWindow()
    {
    }

}