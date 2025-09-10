#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Math.h"
#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    class Camera : public Component
    {
        BASE_SELECTION(Camera, 100)

    public:
        void Awake() override;
        void Update() override;

    protected:
        void DrawInspector() override;

    private:
        class Transform2D* myTransform;
    };
}
