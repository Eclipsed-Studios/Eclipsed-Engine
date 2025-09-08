#pragma once

#include "Math/Math.h"

#include "Components/Component.h"

namespace ENGINE_NAMESPACE
{
    class Camera : public Component
    {
        BASE_COMPONENT(Camera, 100)

    public:
        void Awake() override;
        void Update() override;

    protected:
        void DrawInspector() override;

    private:
        class Transform2D* myTransform;
    };
}
