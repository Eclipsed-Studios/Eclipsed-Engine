#pragma once

#include "Texture.h"
#include "Shaders/Shader.h"
#include "Utilities/Math/Color.h"

namespace Eclipse
{
    class Material
    {
    public:
        Material(const char* myPixelShader = (PathManager::GetAssetDir() / "Shaders/DefaultSpritePixelShader.glsl").generic_string().c_str(), const char* myVertexShader = (PathManager::GetAssetDir() / "Shaders/DefaultSpriteVertexShader.glsl").generic_string().c_str());

        void SetTexture(const char* aPath);
        void Use();

        Shader* myShader;

        ResourcePointer<Texture> myTexture;

        Math::Color color;
    };
}