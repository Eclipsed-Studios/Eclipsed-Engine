#pragma once

namespace ENGINE_NAMESPACE
{
    class Shader
    {
    public:
        Shader() = default;
        ~Shader() = default;

        int Init();
        void Use();

    private:
        unsigned myVertexShader = 0;
        unsigned myFragmentShader = 0;
        unsigned myShaderProgram = 0;
    };
}