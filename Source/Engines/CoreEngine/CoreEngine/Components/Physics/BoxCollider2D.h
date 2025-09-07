#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>

#include "box2d/id.h"

namespace ENGINE_NAMESPACE
{
    class BoxCollider2D : public Collider2D
    {
    public:
        BoxCollider2D() {myUpdateStartPriority = 5;}
        ~BoxCollider2D() = default;

        void Awake() override;

        void OnTransformDirty();

        void SetScale(const Math::Vector2f& aHalfExtents);

    private:
        Math::Vector2f myHalfExtents;
        Math::Vector2f myScale;
        class Transform2D* myTransform;
    };
}