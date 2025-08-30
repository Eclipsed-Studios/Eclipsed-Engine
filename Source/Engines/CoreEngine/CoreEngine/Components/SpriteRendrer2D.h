#pragma once

#include <string>

#include "Components/Component.h"

#include "../GraphicsEngine/Sprite.h"

namespace ENGINE_NAMESPACE
{
    class Sprite;
    class Shader;

    class SpriteRendrer2D : public Component
    {
    public:
        SpriteRendrer2D() = default;
        ~SpriteRendrer2D() = default;

        void Awake() override;
        void LateUpdate() override;

    private:
        Sprite* mySprite;
        Shader* myShader;
    };
}