#pragma once

#include "Components/Component.h"

#include "box2d/id.h"

struct b2Polygon;
namespace ENGINE_NAMESPACE
{
    class Collider2D : public Component
    {
    public:
        Collider2D() = default;
        ~Collider2D() override;

    protected:
        b2ShapeId myInternalCollider;

        // Internals
        b2BodyId myBodyRef;
    };
}
