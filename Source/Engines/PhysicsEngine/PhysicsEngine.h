#pragma once

#include "Math/Vector/Vector2.h"
#include <vector>

#include "box2d/id.h"

#include "PhysicsEngineSettings.h"

struct b2Polygon;

namespace ENGINE_NAMESPACE
{
    class PhysicsEngine
    {
    public:
        class Physics
        {
        public:
            static void SetLinearVelocity(const b2BodyId &aBodyID, const Math::Vector2f &aVelocity);
            static void SetAngularVelocity(const b2BodyId &aBodyID, float aVelocity);

            static Math::Vector2f GetLinearVelocity(const b2BodyId &aBodyID);
            static float GetAngularVelocity(const b2BodyId &aBodyID);

            static Math::Vector2f GetBodyPosition(const b2BodyId &aBodyID);
            static float GetBodyRotation(const b2BodyId &aBodyID);
        };

    public:
        static void CreateRigidBody(b2BodyId *aBody, const RigidBodySettings &aBodySettings, const RigidBodyUserData &, const Math::Vector2f &aStartPosition = {0.f, 0.f});
        static void CreateBoxCollider(b2ShapeId *aShape, const b2BodyId &aBodyID, const Math::Vector2f &aHalfExtents);

        static void RemoveRigidBody(b2BodyId &aBodyID);
        static void RemoveCollider(b2ShapeId &aShape);

        static void Init();
        static void Update();

    private:
        static inline b2WorldId myWorld;
        const static inline Math::Vector2f myGravity = {0.f, -1000.f};

        const static inline int substepCount = 8;
    };
}