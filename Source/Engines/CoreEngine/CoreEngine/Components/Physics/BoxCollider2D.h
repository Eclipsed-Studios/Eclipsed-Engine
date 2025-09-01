#pragma once

#include "Collider2D.h"

#include <Math/Vector/Vector2.h>

#include "box2d/id.h"

namespace ENGINE_NAMESPACE
{
    class BoxCollider2D : public Collider2D
    {
    public:
        BoxCollider2D() = default;
        ~BoxCollider2D() = default;

        // TODO: Add a priority to component Update/Start/Awake etc.
        // Reason this is Start because if RB gets added after BOX it will start afterwards which is wrong
        void Start() override;

        void SetHalfExtents(const Math::Vector2f& aHalfExtents);

    private:
        Math::Vector2f myHalfExtents;
    };
}