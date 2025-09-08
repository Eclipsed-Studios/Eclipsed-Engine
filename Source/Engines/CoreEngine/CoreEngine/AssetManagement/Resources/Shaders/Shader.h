#pragma once

#include <AssetManagement/Resources/Shaders/PixelShader.h>
#include <AssetManagement/Resources/Shaders/VertexShader.h>
#include <AssetManagement/ResourcePointer.h>

namespace ENGINE_NAMESPACE
{
    class Shader
    {
    public:
        Shader() = default;
        ~Shader() = default;

        void Create(const char *aPixelShaderPath, const char *aVertexShaderPath);
        void Use();

        unsigned GetProgramID() { return myProgramID; }

        ResourcePointer<PixelShader>& GetPixelShader() { return myPixelShader; }
        ResourcePointer<VertexShader>& GetVertexShader() { return myVertexShader; }

    private:
        unsigned myProgramID = 0;

        ResourcePointer<PixelShader> myPixelShader;
        ResourcePointer<VertexShader> myVertexShader;
    };
}