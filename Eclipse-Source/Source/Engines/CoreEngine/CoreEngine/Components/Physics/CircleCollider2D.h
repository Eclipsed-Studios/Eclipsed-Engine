#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class CircleCollider2D : public Collider2D
    {
        BASE_SELECTION(CircleCollider2D, 5)

    public:
        void OnSceneLoaded() override;

        void EditorUpdate() override;

        void OnTransformDirty();

        void SetRadius(float aRadius);

    private:
        float LastRadius = 0.f;
        float myInternalRadius = 1.f;

        SERIALIZED_FIELD(float, Radius);

        class Transform2D* myTransform;
    };
}