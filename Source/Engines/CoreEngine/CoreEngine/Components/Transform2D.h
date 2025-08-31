#pragma once

#include "Component.h"

#include <Math/Vector/Vector2.h>

namespace ENGINE_NAMESPACE
{
    class Transform2D : public Component
    {
    public:
        Transform2D() = default;
        ~Transform2D() = default;

        const Math::Vector2f &GetPosition();
        const float GetRotation();
        const Math::Vector2f &GetScale();

        void SetPosition(const Math::Vector2f &aPosition);
        void SetPosition(float aX, float aY);
        
        void SetRotation(float aRotation);

        void SetScale(const Math::Vector2f &aScale);
        void SetScale(float aX, float aY);

    private:
        Math::Vector2f position = {0, 0};
        float rotation = 0;
        Math::Vector2f scale = {1, 1};
    };

}