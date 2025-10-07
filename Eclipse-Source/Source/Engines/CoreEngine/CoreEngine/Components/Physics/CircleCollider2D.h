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
        void CreateCollider() override;

        void DeltaChanges() override;

        void OnTransformDirty() override;

        void SetRadius(float aRadius);

    private:
        float LastRadius = 0.f;
        float myInternalRadius = 1.f;

        SERIALIZED_FIELD_DEFAULT(float, Radius, 1.f);
    };
}