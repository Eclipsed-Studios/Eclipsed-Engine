#pragma once

#include "Collider2D.h"
#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

#include <vector>

namespace Eclipse
{
    class PolygonCollider2D : public Collider2D
    {
        BASE_SELECTION(PolygonCollider2D, 5)

    public:
        void Awake() override;

        void AddPoint(const Math::Vector2f& aPoint);
        
        void OnTransformDirty();

    private:
        std::vector<Math::Vector2f> myPoints; 

        class Transform2D* myTransform;
    };
}