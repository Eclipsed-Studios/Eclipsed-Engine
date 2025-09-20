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
        void OnComponentAdded() override;    


        void Awake() override;

        void EditorUpdate() override;

        void OnTransformDirty();

        void SetScale(const Math::Vector2f& aHalfExtents);

    private:
        Math::Vector2f myHalfExtents;
        SERIALIZED_FIELD_DEFAULT(Math::Vector2f, HalfExtents, Math::Vector2f(0.5f, 0.5f));
        class Transform2D* myTransform;

        Math::Vector2f myLastHalfExtents;
    };
}