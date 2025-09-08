#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>
#include "ECS/ComponentManager.h"

#include "box2d/id.h"

namespace ENGINE_NAMESPACE
{
    class BoxCollider2D : public Collider2D
    {
        DERIVED_COMPONENT(BoxCollider2D, Collider2D, 5)

    public:
        void Awake() override;

        void OnTransformDirty();

        void SetScale(const Math::Vector2f& aHalfExtents);

    protected:
        void DrawInspector() override;

    private:
        Math::Vector2f myHalfExtents;
        Math::Vector2f myScale;
        class Transform2D* myTransform;
    };
}