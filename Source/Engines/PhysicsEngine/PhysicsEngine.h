#pragma once

#include "PhysicsEngineSettings.h"
#include "Math/Vector/Vector2.h"

#include "box2d/id.h"

#include <vector>
#include <functional>

struct b2Polygon;

namespace ENGINE_NAMESPACE
{
    class PhysicsEngine
    {
    public:
        class Physics
        {
        public:
            static void SetLinearVelocity(const b2BodyId& aBodyID, const Math::Vector2f& aVelocity);
            static void SetAngularVelocity(const b2BodyId& aBodyID, float aVelocity);

            static Math::Vector2f GetLinearVelocity(const b2BodyId& aBodyID);
            static float GetAngularVelocity(const b2BodyId& aBodyID);

            static Math::Vector2f GetBodyPosition(const b2BodyId& aBodyID);
            static float GetBodyRotation(const b2BodyId& aBodyID);
        };

    public:
        static bool RayCast(const Ray& aRay, HitResults& aHitResults, float length, Layer aLayerMask = Layer::All);
        static bool OverlapBox(const Math::Vector2f& aPositon, const Math::Vector2f& aHalfExent, HitResults& aHitResults, Layer aLayerMask = Layer::All);
        static bool OverlapSphere(const Math::Vector2f& aPositon, float aRadius, HitResults& aHitResults, Layer aLayerMask = Layer::All);

        static void CreateRigidBody(b2BodyId* aBody, UserData* aUserData, const RigidBodySettings& aBodySettings, const Math::Vector2f& aStartPosition = { 0.f, 0.f });
        static void CreateBoxCollider(b2ShapeId* aShape, const b2BodyId& aBodyID, const Math::Vector2f& aHalfExtents, Layer aLayer);

        static void RemoveRigidBody(b2BodyId& aBodyID);
        static void RemoveCollider(b2ShapeId& aShape);

        static void Init(int aSubstepCount, const Math::Vector2f& aGravity);
        static void Update();

        static void CheckCollisions();

        static inline std::function<void(UserData&)> myBeginContactCallback;
        static inline std::function<void(UserData&)> myEndContactCallback;

    private:
        static inline b2WorldId myWorld;
        static inline Math::Vector2f myGravity;

        static inline int mySubstepCount = 8;
    };
}