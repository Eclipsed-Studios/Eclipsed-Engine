#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "box2d/id.h"

#include "PhysicsEngine/PhysicsEngineSettings.h"

struct b2Polygon;
namespace Eclipse
{
    class ECLIPSED_API Collider2D : public Component
    {
        BASE_SELECTION(Collider2D, 10)

    public:
        void Awake() override;

        void OnDestroy();

        void OnComponentAdded() override;

        SERIALIZED_FIELD_DEFAULT(Layer, myLayer, Layer::Default);
        SERIALIZED_FIELD(Math::Vector2f, ColliderPivot);

        void EditorUpdate() override;

        virtual void OnTransformDirty() {}

    protected:

        virtual void CreateCollider() {}
        virtual void DeltaChanges() {}

    protected:

        UserData myUserData;
        b2ShapeId myInternalCollider;
        Math::Vector2f myLastColliderPivot;

        class Transform2D* myTransform;

        // Internal
        b2BodyId myBodyRef;

    private:
        int myLastLayer;
        bool BodyCreatedByRB = false;

        bool BodyOwned = false;
    };
}
