#pragma once

#include "EclipsedEngine/Components/Component.h"

#include <string>
#include "EntityEngine/ComponentManager.h"

#include "CoreEngine/Math/Vector/Vector2.h"
#include "CoreEngine/Math/Color.h"

#include "AssetEngine/Assets/Material.h"
#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
    class Sprite;
    class Shader;

    class Transform2D;
    
    class ECLIPSED_API SpriteRenderer2D : public Component
    {
        COMPONENT_BASE_2(SpriteRenderer2D, 0)

    public:
        void OnComponentAdded() override;

        void Render() override;
        void Draw(unsigned aProgramID = 0);

        void SetSprite(const char* aPath);
        void SetSprite(const size_t& id);
        void SetSprite(const Texture& aSprite);

        void SetMaterial(const char* aPath);
        void SetMaterial(const size_t& id);
        void SetMaterial(const Material& aMaterial);
        Material* GetMaterial() { return nullptr; }

        void SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax);

        void SetXMirror(bool aMirror);/* { mirroredX = aMirror; }*/
        void SetYMirror(bool aMirror); /*{ mirroredY = aMirror; }*/

        //void DrawInspector() override;

        Math::Vector2f spriteRectMin = { 0.f, 0.f };
        Math::Vector2f spriteRectMax = { 1.f, 1.f };

    private:
        bool hasSprite = false;
        bool hasMaterial = false;

        bool mirroredX = false;
        bool mirroredY = false;

        REPLICATED_SERIALIZED_FIELD(Texture, sprite, SpriteRenderer2D);
        REPLICATED_SERIALIZED_FIELD(Material, material, SpriteRenderer2D);
    };
}