#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Math.h"
#include "ECS/ComponentManager.h"

#include "Reflection/ReflectionDefines.h"

namespace Eclipse
{
    class Camera : public Component
    {
        BASE_SELECTION(Camera, 100)

    public:
        void Awake() override;
        void Render() override;

    protected:
        void DrawInspector() override;

    private:
        class Transform2D* myTransform;
    };
}
