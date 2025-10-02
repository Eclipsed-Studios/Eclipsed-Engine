#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class CapsuleCollider2D : public Collider2D
    {
        BASE_SELECTION(CapsuleCollider2D, 5)

    public:
        void OnSceneLoaded() override;

        void OnTransformDirty();

        void SetRadius(float aRadius);
        void SetHalfHeight(float aHalfHeight);

    private:
        float myInternalRadius;
        float myInternalHalfHeight;

        SERIALIZED_FIELD(float, Radius);
        SERIALIZED_FIELD(float, HalfHeight);

        class Transform2D* myTransform;
    };
}