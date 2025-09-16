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
        SERIALIZED_FIELD(Layer, myLayer);

    protected:
        UserData myUserData;

        b2ShapeId myInternalCollider;

        // Internals
        b2BodyId myBodyRef;
    };
}
