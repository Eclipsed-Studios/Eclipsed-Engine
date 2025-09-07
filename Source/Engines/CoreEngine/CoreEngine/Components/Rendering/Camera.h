#pragma once

#include "Math/Math.h"

#include "Components/Component.h"

namespace ENGINE_NAMESPACE
{
    class Camera : public Component
    {
    public:
        Camera() { myUpdateStartPriority = 100; };
        ~Camera() = default;

        void Awake() override;
        void Update() override;

    private:
        class Transform2D* myTransform;
    };
}
