#pragma once

#include "Collider2D.h"
#include <Utilities/Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

#include <vector>

namespace Eclipse
{
    class PolygonCollider2D : public Collider2D
    {
        BASE_SELECTION(PolygonCollider2D, 5)

    public:
        void CreateCollider() override;

        void DeltaChanges() override;

        void AddPoint(const Math::Vector2f& aPoint);
        
        void OnTransformDirty() override;

    private:
        SERIALIZED_FIELD(std::vector<Math::Vector2f>, myPoints);
        std::vector<Math::Vector2f> myLastPoints;
    };
}