#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "PhysicsEngine/PhysicsEngineSettings.h"

struct b2BodyId;
struct b2ShapeId;

namespace Eclipse
{
    class ECLIPSED_API Collider2D : public Component
    {
        BASE_SELECTION(Collider2D, 5)

    public:
        void OnDestroy();

        void OnComponentAdded() override;

        void EditorUpdate() override;

        virtual void OnTransformDirty() {}

        bool IsBodyOwner() { return BodyOwned; }
        unsigned GetBody() { return myBodyID; }

    protected:
        virtual void CreateCollider() {}
        virtual void DeltaChanges() {}

    public:
        SERIALIZED_FIELD_DEFAULT(Layer, myLayer, Layer::Default);
        SERIALIZED_FIELD(Math::Vector2f, ColliderPivot);

    protected:

        UserData myUserData;
        Math::Vector2f myLastColliderPivot;
        
        class Transform2D* myTransform;

        unsigned myShapeID = 0;
        unsigned myBodyID = 0;

    private:
        int myLastLayer;

        bool BodyOwned = false;
    };
}
