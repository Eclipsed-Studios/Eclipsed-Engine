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
        void Awake() override;

        void OnTransformDirty();

        void SetRadius(float aRadius);

    private:
        SERIALIZED_FIELD(float, myRadius);

        SERIALIZED_FIELD(float, myRealRadius);

        class Transform2D* myTransform;
    };
}