#pragma once

#include "EclipsedEngine/Components/Component.h"

#include <string>
#include "EntityEngine/ComponentManager.h"

#include "CoreEngine/Math/Vector/Vector2.h"
#include "CoreEngine/Math/Color.h"

#include "AssetEngine/Assets/Material.h"

namespace Eclipse
{
    class Sprite;
    class Shader;

    class Transform2D;

    class SpriteRenderer2D : public Component
    {
        COMPONENT_BASE_2(SpriteRenderer2D, 0)

    public:
        void OnComponentAdded() override;

        void Render() override;
        void Draw(unsigned aProgramID = 0);

        void SetTexture(const char* aPath);
        void SetTexture(const size_t& id);

        void SetMaterial(const char* aPath);
        void SetMaterial(const size_t& id);
        Material* GetMaterial() { return nullptr; }

        void SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax);

        void SetXMirror(bool aMirror) { mirroredX = aMirror; }
        void SetYMirror(bool aMirror) { mirroredY = aMirror; }

        //void DrawInspector() override;

        Math::Vector2f spriteRectMin = { 0.f, 0.f };
        Math::Vector2f spriteRectMax = { 1.f, 1.f };

    private:
        Texture sprite;
        Material material;

        bool hasTexture = false;
        bool hasMaterial = false;


        bool mirroredX = false;
        bool mirroredY = false;

        PRIVATE_SERIALIZED_FIELD_DEFAULT(size_t, materialID, 0);
        PRIVATE_SERIALIZED_FIELD_DEFAULT(size_t, textureID, 0);


        SERIALIZED_FIELD(Material, matmat);
    };
}