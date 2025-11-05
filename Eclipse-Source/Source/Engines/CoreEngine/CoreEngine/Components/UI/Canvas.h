#pragma once

#include "CoreEngine/ECS/ComponentManager.h"
#include "CoreEngine/Components/Base/BaseComponent.h"

namespace Eclipse
{
    class Canvas : public Component
    {
        BASE_SELECTION(Canvas, FLT_MAX);

    public:

        void SetCanvasTransformProperties();
        void EditorUpdate() override;

        SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, ReferenceResolution, Math::Vector2f(1920, 1080));
        SERIALIZED_FIELD_DEFAULT(bool, WorldSpace, false);

        struct EditorCanvasCameraTransform
        {
            Math::Vector2f PositionOffset = { 0, 0 };
            float Rotation = 0.f;
            Math::Vector2f ScaleMultiplier = { 1, 1 };
        } canvasCameraTransform;

        static inline bool drawCanvasGizmos = true;

    };
}