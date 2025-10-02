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
        SERIALIZED_FIELD_DEFAULT(Layer, myLayer, Layer::Default);
        SERIALIZED_FIELD(Math::Vector2f, ColliderPivot);

    protected:
        UserData myUserData;

        b2ShapeId myInternalCollider;

        Math::Vector2f myLastColliderPivot;

        // Internals
        b2BodyId myBodyRef;

        bool myCreatedInternally = false;
    };
}
