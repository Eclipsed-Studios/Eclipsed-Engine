#pragma once

#include "Component.h"

#include <Vector/Vector2.h>

namespace ENGINE_NAMESPACE
{
    class Transform2D : public Component
    {
    public:
        Transform2D() = default;
        ~Transform2D() = default;

        const Math::Vector2f &GetPosition() { return position; }
        const Math::Vector2f &GetScale() { return scale; }
        const float GetRotation() { return rotation; }

        void GetPosition() { return position; }
        void GetScale() { return scale; }
        void GetRotation() { return rotation; }

    private:
        Math::Vector2f position;
        Math::Vector2f scale;
        float rotation;
    };

}