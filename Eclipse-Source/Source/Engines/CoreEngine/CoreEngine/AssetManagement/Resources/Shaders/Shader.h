#pragma once

#include <../CoreEngine/CoreEngine/AssetManagement/Resources/Shaders/PixelShader.h>
#include <../CoreEngine/CoreEngine/AssetManagement/Resources/Shaders/VertexShader.h>
#include <../CoreEngine/CoreEngine/AssetManagement/ResourcePointer.h>

namespace Eclipse
{
    class Shader
    {
    public:
        Shader() = default;
        ~Shader() = default;

        void Create(const char *aPixelShaderPath, const char *aVertexShaderPath);
        void Use(unsigned aProgramID);

        unsigned GetProgramID() { return myProgramID; }

        ResourcePointer<PixelShader>& GetPixelShader() { return myPixelShader; }
        ResourcePointer<VertexShader>& GetVertexShader() { return myVertexShader; }

    private:
        unsigned myProgramID = 0;

        ResourcePointer<PixelShader> myPixelShader;
        ResourcePointer<VertexShader> myVertexShader;
    };
}