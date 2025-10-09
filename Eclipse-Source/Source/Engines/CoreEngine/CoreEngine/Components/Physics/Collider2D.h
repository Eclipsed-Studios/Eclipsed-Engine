#pragma once

#include "Components/Base/BaseComponent.h"

#include "box2d/id.h"
#include "PhysicsEngineSettings.h"
#include "ECS/ComponentManager.h"

struct b2Polygon;
namespace Eclipse
{
    class Collider2D : public Component
    {
        BASE_SELECTION(Collider2D)

    public:
        //~Collider2D();

    public:
        void OnDestroy();

        void OnComponentAdded() override;
        void OnSceneLoaded() override;

        SERIALIZED_FIELD_DEFAULT(Layer, myLayer, Layer::Default);
        SERIALIZED_FIELD(Math::Vector2f, ColliderPivot);

        void EditorUpdate() override;

        virtual void OnTransformDirty() {}

    protected:

        virtual void CreateCollider() = 0;
        virtual void DeltaChanges() {}

    protected:

        UserData myUserData;
        b2ShapeId myInternalCollider;
        Math::Vector2f myLastColliderPivot;

        // Internals
        b2BodyId myBodyRef;

        class Transform2D* myTransform;

    private:
        bool myCreatedInternally = false;

        int myLastLayer;
    };
}
