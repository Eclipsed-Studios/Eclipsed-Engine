#pragma once

#include <string>

#include "Components/Component.h"

#include "../GraphicsEngine/Sprite.h"

#include "AssetManagement/Resources.h"
#include "Math/Color.h"

#include "Math/Vector/Vector2.h"

namespace ENGINE_NAMESPACE
{
    class Material
    {
    public:
        Material();

        void SetTexture(const char* aPath);
        void Use();

        Shader* myShader;

        ResourcePointer<Texture> myTexture;

        Math::Color color;
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

        void SetMaterial(Material* aMaterial);
        
        void SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax);

        void SetXMirror(bool aMirror) { mirroredX = aMirror; }
        void SetYMirror(bool aMirror) { mirroredY = aMirror; }

    private:
        Sprite* mySprite;
        Material* myMaterial;

        Math::Vector2f spriteRectMin = { 0.f, 0.f };
        Math::Vector2f spriteRectMax = { 1.f, 1.f };

        Transform2D* myTransform;

        bool mirroredX = false;
        bool mirroredY = false;
    };
}