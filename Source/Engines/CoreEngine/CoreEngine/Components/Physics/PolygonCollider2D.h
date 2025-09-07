#pragma once

#include "Collider2D.h"
#include <Math/Vector/Vector2.h>
#include "box2d/id.h"

#include <vector>

namespace ENGINE_NAMESPACE
{
    class PolygonCollider2D : public Collider2D
    {
    public:
        PolygonCollider2D() {myUpdateStartPriority = 5;}
        ~PolygonCollider2D() = default;

        void Awake() override;

        void AddPoint(const Math::Vector2f& aPoint);
        
        void OnTransformDirty();

    private:
        std::vector<Math::Vector2f> myPoints;

        class Transform2D* myTransform;
    };
}