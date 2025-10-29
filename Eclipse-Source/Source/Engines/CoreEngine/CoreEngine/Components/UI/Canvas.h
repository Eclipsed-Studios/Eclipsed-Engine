#pragma once

#include "CoreEngine/ECS/ComponentManager.h"
#include "CoreEngine/Components/Base/BaseComponent.h"

namespace Eclipse
{
    class Canvas : public Component
    {
        BASE_SELECTION(Canvas, FLT_MAX);

    public:

        void EditorUpdate() override;

        void OnComponentAdded() override
        {
            if (!main)
                main = this;
        }

        void OnDestroy() override
        {
            if (main == this)
                main = nullptr;
        }

        static inline Canvas* main;

        SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, ReferenceResolution, Math::Vector2f(1920, 1080));
        //SERIALIZED_FIELD_DEFAULT(bool, WorldSpace, false);

        static inline struct EditorCanvasCameraTransform
        {
            Math::Vector2f PositionOffset = { 0, 0 };
            Math::Vector2f ScaleMultiplier = { 1, 1 };
            //Math::Vector2f InspectorScale = { 0, 0 };
            float Rotation;
        } canvasCameraTransform;

        static inline bool drawCanvasGizmos = true;

    };
}