#pragma once

#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Components/Component.h"
#include "CoreEngine/GraphicsBuffers/CanvasBuffer.h"

ECLIPSED_CLASS;


namespace Eclipse
{
    class Canvas : public Component
    {
        COMPONENT_BASE_2(Canvas, 999999);

    public:

        void SetCanvasTransformProperties();
        void EditorUpdate() override;
        void OnComponentAdded() override;

        void TransformUpdate();

        Math::Vector2f ReferenceResolution = Math::Vector2f(1920, 1080);
        bool WorldSpace = false;

        struct EditorCanvasCameraTransform
        {
            Math::Vector2f PositionOffset = { 0, 0 };
            float Rotation = 0.f;
            Math::Vector2f ScaleMultiplier = { 1, 1 };
        } canvasCameraTransform;

        static inline bool drawCanvasGizmos = true;

        CanvasBuffer myCanvasBuffer;

        static inline bool IsScene = false;
    };
}
