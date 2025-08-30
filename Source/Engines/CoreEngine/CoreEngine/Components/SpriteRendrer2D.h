#pragma once

#include <string>

#include "Components/Component.h"

#include "../GraphicsEngine/Sprite.h"

namespace ENGINE_NAMESPACE
{
    class Material
    {
    public:
        Material() = default;

        void SetTexture(const char* aPath);
        void Use();

        Shader *myShader;

        // Texture should be here not unsigned
        unsigned myTextureID;
    };

    class Sprite;
    class Shader;

    class Transform2D;

    class SpriteRendrer2D : public Component
    {
    public:
        SpriteRendrer2D() = default;
        ~SpriteRendrer2D() = default;

        void Awake() override;
        void Start() override;

        void LateUpdate() override;

    private:
        Sprite *mySprite;
        Material myMaterial;

        Transform2D *myTransform;
    };
}