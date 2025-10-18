#pragma once

#ifdef ECLIPSED_EDITOR
#include "Windows/WindowManager.h"

#include "Utilities/ErrorCodes.h"

#include <string>

struct GLFWwindow;
struct ImFont;

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

        static void DrawPlayGameButtons();

    private:
        static void LoadFonts();

    private:
        static inline GLFWwindow* myWindow;

        static inline WindowManager myWindowManager;

        static inline std::string firstSceneOnPlay;

    public:
        static inline ImFont* fontTiny = nullptr;
        static inline ImFont* fontSmall = nullptr;
        static inline ImFont* fontMedium= nullptr;
        static inline ImFont* fontLarge= nullptr;
        static inline ImFont* fontExtraLarge = nullptr;
    };
}
#endif