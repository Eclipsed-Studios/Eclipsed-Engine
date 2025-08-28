#pragma once

#include "ErrorCodes.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE
{
    class Editor
    {
    public:
        Editor(/* args */) = default;
        ~Editor() = default;

        ErrorCode Init();
        void Begin();
        void Update();
        void Render();
        void End();

    private:
        GLFWwindow* myWindow;

        unsigned vertexBuffer = 0;
        unsigned vertexShader = 0;
        unsigned fragmentShader = 0;
        unsigned program = 0;

        unsigned indexVertexBuffer = 0;
    };

}