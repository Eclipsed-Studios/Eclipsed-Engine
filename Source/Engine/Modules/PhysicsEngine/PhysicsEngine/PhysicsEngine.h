#pragma once

#include "PhysicsEngineSettings.h"
#include "CoreEngine/Math/Vector/Vector2.h"

#include "box2d/id.h"
#include "box2d/types.h"

#include <vector>
#include <functional>

#include <array>

namespace Eclipse
{
    namespace Editor
    {
        class GameSettingsWindow;
    }

    class Physics
    {
    public:
        static void SetLinearVelocity(const b2BodyId* aBodyID, const Math::Vector2f& aVelocity);
        static void SetAngularVelocity(const b2BodyId* aBodyID, float aVelocity);

        static Math::Vector2f GetLinearVelocity(const b2BodyId* aBodyID);
        static float GetAngularVelocity(const b2BodyId* aBodyID);

        static Math::Vector2f GetBodyPosition(const b2BodyId* aBodyID);
        static float GetBodyRotation(const b2BodyId* aBodyID);
    };
    
    class PhysicsEngine
    {
        friend class Editor::GameSettingsWindow;

    public:

        static PhysicsEngine* Instance;
        static PhysicsEngine& Get()
        {
            return *Instance;
        }

    public:
        bool RayCast(const Ray& aRay, HitResults& aHitResults, float length, Layer aLayerMask = Layer::All);
        bool OverlapBox(const Math::Vector2f& aPositon, const Math::Vector2f& aHalfExent, HitResults& aHitResults, Layer aLayerMask = Layer::All);
        bool OverlapSphere(const Math::Vector2f& aPositon, float aRadius, HitResults& aHitResults, Layer aLayerMask = Layer::All);

        void CreateRigidBody(b2BodyId* aBody,
            UserData* aUserData,
            Box2DBodyType BodyType = StaticBody,
            bool LockRotation = false,
            bool LockXPos = false,
            bool LockYPos = false,
            const Math::Vector2f& aStartPosition = { 0.f, 0.f });

        // Simple
        void CreateBoxCollider(b2ShapeId* aShape, const b2BodyId* aBodyID, const Math::Vector2f& aHalfExtents, Layer aLayer);
        void CreateCircleCollider(b2ShapeId* aShape, const b2BodyId* aBodyID, float radius, Layer aLayer);
        void CreateCapsuleCollider(b2ShapeId* aShape, const b2BodyId* aBodyID, float aHalfHeight, float aRadius, Layer aLayer);

        // Complex
        bool CreatePolygonCollider(b2ShapeId* aShape, const b2BodyId* aBodyID, const std::vector<Math::Vector2f>& aPolygonPoints, Layer aLayer);

        void DeleteShape(b2ShapeId* aShape);
        void DeleteBody(b2BodyId* aBody);
        
        void SetBodyMass(b2BodyId* aBody, float aMass);
        
        void SetPhysicsMaterial(b2ShapeId* aShape, const PhysMaterial& material);
        void ChangeLayer(b2ShapeId* aShapeID, Layer aLayer);
        void ChangeBodyType(b2BodyId* aBodyID, BodyType aBodyType);
        void ChangeRBLocks(b2BodyId* aBodyID, bool XLock, bool YLock, bool RotationLock);

        void RemoveRigidBody(b2BodyId* aBodyID);
        void RemoveCollider(b2ShapeId* aShape);

        void SetTransform(b2BodyId* aBodyID, const Math::Vector2f& aPosition, float aRotation);

        // Update Simple collisions
        void SetTransformBox(b2ShapeId* aShapeID, const Math::Vector2f& aScale, const Math::Vector2f& aPivot = { 0.f, 0.f });
        void SetTransformCircle(b2ShapeId* aShapeID, float aRadius, const Math::Vector2f& aPivot = { 0.f, 0.f });
        void SetTransformCapsule(b2ShapeId* aShapeID, float aRadius, float aHalfHeight, const Math::Vector2f& aPivot = { 0.f, 0.f });

        // Update Complex collisions
        void SetTransformPolygon(b2ShapeId* aShapeID, const std::vector<Math::Vector2f>& aPoints, const Math::Vector2f& aScale, const Math::Vector2f& aPivot = { 0.f, 0.f });

        void SetGravity(const Math::Vector2f& aGravity);

        void InitWorld();
        void Init(PhysicsEngine& aPhysicsEngine, int aSubstepCount, const Math::Vector2f& aGravity, b2DebugDraw& aDebugdraw);
        void Update();
        void CleanUp();
        void DrawPhysicsObjects();


        void CheckCollisions();

        bool& GetDebugDraw();
        bool& GetDebugDrawShapes(DebugDrawTypes aType);

        void LoadLayers();

        std::function<void(UserData&)> myBeginContactCallback;
        std::function<void(UserData&)> myEndContactCallback;

    private:
        std::array<uint64_t, MAX_LAYERS> myCollisionLayers = {};

        b2WorldId myWorld;
        Math::Vector2f myGravity;
        int mySubstepCount = 8;

        b2DebugDraw myDebugDraw;
        bool myDrawDebugShapes = true;
        bool myDrawQueries = false;

        bool myHasCreatedWorld;
    };
}