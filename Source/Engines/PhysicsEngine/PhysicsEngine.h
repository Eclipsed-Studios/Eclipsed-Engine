#pragma once

#include "Math/Vector/Vector2.h"
#include <vector>

#include "box2d/id.h"

namespace ENGINE_NAMESPACE
{
    class PhysicsEngine
    {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        static b2BodyId *CreateRigidBody(const Math::Vector2f &aStartPosition = {0.f, 0.f});

        static void Init();
        static void Update();

    private:
        static inline b2WorldId myWorld;
        static inline std::vector<b2BodyId> myBodies;
        static inline Math::Vector2f myGravity = {0.f, -1000.f};

        const static int substepCount = 4;
    };
}