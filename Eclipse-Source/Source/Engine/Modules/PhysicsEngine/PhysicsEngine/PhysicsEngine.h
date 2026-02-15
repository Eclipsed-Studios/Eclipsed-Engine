#pragma once

#include "PhysicsEngineSettings.h"
#include "CoreEngine/Math/Vector/Vector2.h"

#include "box2d/id.h"
#include "box2d/types.h"

#include <vector>
#include <functional>

#include <array>

#include <unordered_map>


namespace Eclipse
{
    class PhysicsEngine
    {
    public:
        class Physics
        {
        public:
            static void SetLinearVelocity(unsigned aBodyID, const Math::Vector2f& aVelocity);
            static void SetAngularVelocity(unsigned aBodyID, float aVelocity);

            static Math::Vector2f GetLinearVelocity(unsigned aBodyID);
            static float GetAngularVelocity(unsigned aBodyID);

            static Math::Vector2f GetBodyPosition(unsigned aBodyID);
            static float GetBodyRotation(unsigned aBodyID);
        };

    public:
        static bool RayCast(const Ray& aRay, HitResults& aHitResults, float length, Layer aLayerMask = Layer::All);
        static bool OverlapBox(const Math::Vector2f& aPositon, const Math::Vector2f& aHalfExent, HitResults& aHitResults, Layer aLayerMask = Layer::All);
        static bool OverlapSphere(const Math::Vector2f& aPositon, float aRadius, HitResults& aHitResults, Layer aLayerMask = Layer::All);



        static unsigned CreateRigidBody(
            UserData* aUserData,
            Box2DBodyType BodyType = StaticBody,
            bool LockRotation = false,
            bool LockXPos = false,
            bool LockYPos = false,
            const Math::Vector2f& aStartPosition = { 0.f, 0.f });

        // Simple
        static unsigned CreateBoxCollider(unsigned aBodyID, const Math::Vector2f& aHalfExtents, Layer aLayer);
        static unsigned CreateCircleCollider(unsigned aBodyID, float radius, Layer aLayer);
        static unsigned CreateCapsuleCollider(unsigned aBodyID, float aHalfHeight, float aRadius, Layer aLayer);

        // Complex
        static unsigned CreatePolygonCollider(unsigned aBodyID, const std::vector<Math::Vector2f>& aPolygonPoints, Layer aLayer);

        static void DeleteShape(unsigned aShapeID);
        static void DeleteBody(unsigned aBodyID);
        
        static void ChangeLayer(unsigned aShapeID, Layer aLayer);
        static void ChangeBodyType(unsigned aBodyID, BodyType aBodyType);
        static void ChangeRBLocks(unsigned aBodyID, bool XLock, bool YLock, bool RotationLock);

        static void SetPosition(unsigned aBodyID, const Math::Vector2f& aPosition);
        static void SetRotation(unsigned aBodyID, float aRotation);

        static void SetTransform(unsigned aBodyID, const Math::Vector2f& aPosition, float aRotation);

        // Update Simple collisions
        static void SetTransformBox(unsigned aBodyID, const Math::Vector2f& aPosition, float aRotation, const Math::Vector2f& aScale, const Math::Vector2f& aPivot = { 0.f, 0.f });
        static void SetTransformCircle(unsigned aBodyID, const Math::Vector2f& aPosition, float aRotation, float aRadius, const Math::Vector2f& aPivot = { 0.f, 0.f });
        static void SetTransformCapsule(unsigned aBodyID, const Math::Vector2f& aPosition, float aRotation, float aRadius, float aHalfHeight, const Math::Vector2f& aPivot = { 0.f, 0.f });

        // Update Complex collisions
        static void SetTransformPolygon(unsigned aBodyID, const Math::Vector2f& aPosition, float aRotation, const std::vector<Math::Vector2f>& aPoints, const Math::Vector2f& aScale, const Math::Vector2f& aPivot = { 0.f, 0.f });

        static void SetGravity(const Math::Vector2f& aGravity);

        static void InitWorld();
        static void Init(int aSubstepCount, const Math::Vector2f& aGravity, b2DebugDraw& aDebugdraw);
        static void Update();
        static void CleanUp();
        static void DrawPhysicsObjects();


        static void CheckCollisions();

        static bool& GetDebugDraw();
        static bool& GetDebugDrawShapes(DebugDrawTypes aType);

        static void LoadLayers();

        static inline std::function<void(UserData&)> myBeginContactCallback;
        static inline std::function<void(UserData&)> myEndContactCallback;

        static inline std::array<uint64_t, MAX_LAYERS> myCollisionLayers = {};

        static inline std::unordered_map<unsigned, b2BodyId> myBodyIdRegistry;
        static inline std::unordered_map<unsigned, b2ShapeId> myShapeIdRegistry;
        static inline std::unordered_map<unsigned, b2ChainId> myChainIdRegistry;

    private:
        static inline b2WorldId myWorld;
        static inline Math::Vector2f myGravity;
        static inline int mySubstepCount = 4;

        static inline b2DebugDraw myDebugDraw;
        static inline bool myDrawDebugShapes = true;
        static inline bool myDrawQueries = false;

        static inline bool myHasCreatedWorld;

        static inline unsigned IDCounter = 1;

        static inline unsigned GetNextIdCounter(){ return IDCounter++; }
    };
}