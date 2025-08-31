#pragma once

#include "ErrorCodes.h"

struct GLFWwindow;

namespace ENGINE_NAMESPACE
{
    class GraphicsEngine
    {
    public:
        GraphicsEngine() = default;
        ~GraphicsEngine() = default;

        static GraphicsEngine &Get()
        {
            static GraphicsEngine instance;
            return instance;
        }

        ErrorCode Init();
        void Begin();
        void Render();
        void End();

        int ShouldWindowClose();
        
        ErrorCode CheckErrorCodes(ErrorCode aErrorCode);

    private:
        GLFWwindow *myWindow;

    private:
        ErrorCode InitOpenGL();
        ErrorCode CreateWindow();
    };
}
