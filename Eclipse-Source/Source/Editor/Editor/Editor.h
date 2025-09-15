#pragma once

#include "WindowManager.h"

#include "ErrorCodes.h"

#include <string>

struct GLFWwindow;

namespace Eclipse::Editor
{
    class EditorContext
    {
    public:
        static ErrorCode Init();
        static bool BeginFrame();
        static void Update();
        static void Render();
        static void EndFrame();

        static void End();

    private:
        static inline GLFWwindow* myWindow;

        static inline WindowManager myWindowManager;

        static inline std::string firstSceneOnPlay;
    };
}