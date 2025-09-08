#pragma once

#include <string>
#include "ECS/ComponentManager.h"

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

        void BindTexture();
    };

    class Sprite;
    class Shader;

    class Transform2D;

    class SpriteRenderer2D : public Component
    {
        BASE_COMPONENT(SpriteRenderer2D, 0)

    public:
        void Awake() override;
        void Start() override;

        void LateUpdate() override;

        void SetMaterial(Material* aMaterial);
        const Material* GetMaterial() { return myMaterial; }

        void SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax);

        void SetXMirror(bool aMirror) { mirroredX = aMirror; }
        void SetYMirror(bool aMirror) { mirroredY = aMirror; }


    protected:
        void DrawInspector() override;


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