#pragma once

#include "ErrorCodes.h"

#include "CoreEngine/ECS/ComponentManager.h"



struct GLFWwindow;

namespace ENGINE_NAMESPACE
{
    class Sprite;
    class Shader;

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
        GLFWwindow *myWindow;

        ComponentManager componentManager;
    };

}