#pragma once

#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Components/Component.h"



namespace Eclipse
{
    class RectTransform : public Component
    {
        COMPONENT_BASE_2(RectTransform, FLT_MAX)

    public:
        void EarlyUpdate() override;
        //void DrawInspector() override;

    public:
        PRIVATE_SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, Position, Math::Vector2f(0, 0));
        PRIVATE_SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, WidthHeightPX, Math::Vector2f(100, 100));

        class Canvas* myCanvas;
    };
}