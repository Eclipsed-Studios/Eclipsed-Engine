#pragma once

#include "Components/Component.h"

#include "box2d/id.h"
#include "PhysicsEngineSettings.h"

struct b2Polygon;
namespace ENGINE_NAMESPACE
{
    class Collider2D : public Component
    {
    public:
        Collider2D() = default;
        ~Collider2D() override;

        Layer myLayer = Layer::Default;

    protected:
        UserData myUserData;

        b2ShapeId myInternalCollider;

        // Internals
        b2BodyId myBodyRef;
    };
}
