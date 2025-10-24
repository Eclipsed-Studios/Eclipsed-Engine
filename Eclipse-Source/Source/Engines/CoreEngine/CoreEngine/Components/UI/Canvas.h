#pragma once

#include "CoreEngine/ECS/ComponentManager.h"
#include "CoreEngine/Components/Base/BaseComponent.h"

namespace Eclipse
{
    class Canvas : public Component
    {
        BASE_SELECTION(Canvas, FLT_MAX)

            void EarlyUpdate() override;

        void Awake()
        {
            if (!main)
                main = this;
        }

    public:
        static inline Canvas* main;

        SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, ReferenceResolution, Math::Vector2f(1920, 1080));

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