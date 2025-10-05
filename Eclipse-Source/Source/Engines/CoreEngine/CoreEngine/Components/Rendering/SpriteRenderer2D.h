#pragma once

#include "Components/Base/BaseComponent.h"

#include <string>
#include "ECS/ComponentManager.h"

#include "AssetManagement/Resources.h"
#include "Math/Color.h"

#include "Math/Vector/Vector2.h"

namespace Eclipse
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

    class SpriteRenderer2D : public Component
    {
        BASE_SELECTION(SpriteRenderer2D, 0)

    public:
        void OnDestroy() override;

        void OnSceneLoaded() override;
        void Start() override;

        void Render() override;
        void Draw(unsigned aProgramID = 0);

        void SetTexture(const char* aPath);
        Material* GetMaterial() { return myMaterial; }

        void SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax);

        void SetXMirror(bool aMirror) { mirroredX = aMirror; }
        void SetYMirror(bool aMirror) { mirroredY = aMirror; }

        void DrawInspector() override;

        Math::Vector2f spriteRectMin = { 0.f, 0.f };
        Math::Vector2f spriteRectMax = { 1.f, 1.f };

    private:
        Sprite* mySprite;
        Material* myMaterial = nullptr;


        bool mirroredX = false;
        bool mirroredY = false;

        bool hasTexture = false;

    private:
        PRIVATE_SERIALIZED_FIELD_DEFAULT(std::string, myTexturePath, "");
    };
}