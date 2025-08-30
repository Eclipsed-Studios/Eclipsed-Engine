#pragma once

#include "ErrorCodes.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE::Editor
{
    class Sprite;
    class Shader;

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

    private:
        GLFWwindow *myWindow;
    };

}