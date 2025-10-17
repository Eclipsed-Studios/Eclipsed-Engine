#pragma once

#include "Collider2D.h"

#include <Utilities/Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

namespace Eclipse
{
    class BoxCollider2D : public Collider2D
    {
        BASE_SELECTION(BoxCollider2D, 5)

    public:
        void CreateCollider() override;

        void DeltaChanges() override;

        void OnTransformDirty() override;

        void SetScale(const Math::Vector2f& aHalfExtents);

    private:
        Math::Vector2f myHalfExtents;
        SERIALIZED_FIELD_DEFAULT(Math::Vector2f, HalfExtents, Math::Vector2f(0.5f, 0.5f));

        Math::Vector2f myLastHalfExtents;
    };
}