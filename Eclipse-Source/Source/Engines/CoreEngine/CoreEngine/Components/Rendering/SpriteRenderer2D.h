#pragma once

#include "CoreEngine/Components/Base/BaseComponent.h"

#include <string>
#include "CoreEngine/ECS/ComponentManager.h"

#include "CoreEngine/AssetManagement/Resources.h"

#include "Utilities/Math/Vector/Vector2.h"
#include "Utilities/Math/Color.h"

#include "CoreEngine/AssetManagement/Resources/Material.h"

#include "AssetEngine/Assets/Material.h"

namespace Eclipse
{
    class Sprite;
    class Shader;

    class Transform2D;

    class SpriteRenderer2D : public Component
    {
        BASE_SELECTION(SpriteRenderer2D, 0)

    public:
        void OnComponentAdded() override;

        void Start() override;

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

        void DrawInspector() override;

        Math::Vector2f spriteRectMin = { 0.f, 0.f };
        Math::Vector2f spriteRectMax = { 1.f, 1.f };

    private:
        Textures sprite;
        Materials material;

        bool hasTexture = false;
        bool hasMaterial = false;


        bool mirroredX = false;
        bool mirroredY = false;

    private:
        PRIVATE_SERIALIZED_FIELD_DEFAULT(std::string, myTexturePath, "");
    };
}