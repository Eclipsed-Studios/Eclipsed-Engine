#pragma once

#include "Collider2D.h"

#include <Utilities/Math/Vector/Vector2.h>
#include "EntityEngine/ComponentManager.h"

namespace Eclipse
{
    class CapsuleCollider2D : public Collider2D
    {
        BASE_SELECTION(CapsuleCollider2D, 5)

    public:
        void CreateCollider() override;

        void OnTransformDirty();

        void SetRadius(float aRadius);
        void SetHalfHeight(float aHalfHeight);

    private:
        float myInternalRadius;
        float myInternalHalfHeight;

        SERIALIZED_FIELD(float, Radius);
        SERIALIZED_FIELD(float, HalfHeight);
    };
}