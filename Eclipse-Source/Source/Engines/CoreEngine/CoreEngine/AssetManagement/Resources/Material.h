#pragma once

#include "Texture.h"
#include "Shaders/Shader.h"
#include "Utilities/Math/Color.h"

namespace Eclipse
{
    class Material
    {
    public:
        Material(const char* myPixelShader = ASSET_PATH"Shaders/DefaultSpritePixelShader.glsl", const char* myVertexShader = ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");

        void SetTexture(const char* aPath);
        void Use();

        Shader* myShader;

        ResourcePointer<Texture> myTexture;

        Math::Color color;
    };
}