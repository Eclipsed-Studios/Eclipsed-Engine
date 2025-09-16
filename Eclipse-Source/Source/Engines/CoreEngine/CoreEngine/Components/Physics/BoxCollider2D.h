#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class BoxCollider2D : public Collider2D
    {
        BASE_SELECTION(BoxCollider2D, 5)

    public:
        void Awake() override;

        void OnTransformDirty();

        void SetScale(const Math::Vector2f& aHalfExtents);

    private:
        SERIALIZED_FIELD(Math::Vector2f, myHalfExtents);
        SERIALIZED_FIELD(Math::Vector2f, myScale);
        class Transform2D* myTransform;
    };
}