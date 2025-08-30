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

        const Math::Vector2f &GetPosition() { return position; }
        const float GetRotation() { return rotation; }
        const Math::Vector2f &GetScale() { return scale; }

        void SetPosition(const Math::Vector2f &aPosition) { position = aPosition; }
        void SetRotation(float aRotation) { rotation = aRotation; }
        void SetScale(const Math::Vector2f &aScale) { scale = aScale; }

    private:
        Math::Vector2f position;
        float rotation;
        Math::Vector2f scale;
    };

}