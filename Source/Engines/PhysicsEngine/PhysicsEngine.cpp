#include "PhysicsEngine.h"

#include "Timer.h"

#include "box2d/box2d.h"

namespace ENGINE_NAMESPACE
{
#pragma region PhysicsHelperFunctions
    void PhysicsEngine::Physics::SetLinearVelocity(const b2BodyId& aBodyID, const Math::Vector2f& aVelocity)
    {
        b2Vec2 box2DVec2(aVelocity.x, aVelocity.y);
        b2Body_SetLinearVelocity(aBodyID, box2DVec2);
    }
    void PhysicsEngine::Physics::SetAngularVelocity(const b2BodyId& aBodyID, float aVelocity)
    {
        b2Body_SetAngularVelocity(aBodyID, aVelocity);
    }

    Math::Vector2f PhysicsEngine::Physics::GetLinearVelocity(const b2BodyId& aBodyID)
    {
        b2Vec2 velocityB2 = b2Body_GetLinearVelocity(aBodyID);
        return { velocityB2.x, velocityB2.y };
    }
    float PhysicsEngine::Physics::GetAngularVelocity(const b2BodyId& aBodyID)
    {
        float velocity = b2Body_GetAngularVelocity(aBodyID);
        return velocity;
    }

    Math::Vector2f PhysicsEngine::Physics::GetBodyPosition(const b2BodyId& aBodyID)
    {
        b2Vec2 position = b2Body_GetPosition(aBodyID);
        return { position.x, position.y };
    }
    float PhysicsEngine::Physics::GetBodyRotation(const b2BodyId& aBodyID)
    {
        b2Rot rotation = b2Body_GetRotation(aBodyID);
        return b2Rot_GetAngle(rotation);
    }

#pragma endregion

    void PhysicsEngine::RemoveRigidBody(b2BodyId& aBodyID)
    {
        b2DestroyBody(aBodyID);
        aBodyID = b2_nullBodyId;
    }

    void PhysicsEngine::RemoveCollider(b2ShapeId& aShape)
    {
        b2DestroyShape(aShape, false);
    }

    void PhysicsEngine::CreateRigidBody(b2BodyId* aBody, const RigidBodySettings& aBodySettings, const Math::Vector2f& aStartPosition)
    {
        b2BodyDef bodyDefine = b2DefaultBodyDef();

        b2MotionLocks motionLocks(aBodySettings.LockXPos, aBodySettings.LockYPos, aBodySettings.LockRotation);
        bodyDefine.motionLocks = motionLocks;

        bodyDefine.type = static_cast<b2BodyType>(aBodySettings.BodyType);
        bodyDefine.position = b2Vec2(aStartPosition.x, aStartPosition.y);

        bodyDefine.linearDamping = 5.f;

        //bodyDefine.userData = reinterpret_cast<void*>(&aUserData);

        *aBody = b2CreateBody(myWorld, &bodyDefine);
    }

    void PhysicsEngine::CreateBoxCollider(b2ShapeId* aShape, UserData* aUserData, const b2BodyId& aBodyID, const Math::Vector2f& aHalfExtents, Layer aLayer)
    {
        b2Polygon polygon = b2MakeBox(aHalfExtents.x, aHalfExtents.y);
        b2ShapeDef shapeDef = b2DefaultShapeDef();

        shapeDef.filter.categoryBits = static_cast<uint64_t>(aLayer);

        shapeDef.userData = aUserData;

        *aShape = b2CreatePolygonShape(aBodyID, &shapeDef, &polygon);
    }

    void PhysicsEngine::Init()
    {
        b2WorldDef worldDef;
        worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2(myGravity.x, myGravity.y);
        myWorld = b2CreateWorld(&worldDef);

        b2ShapeProxy boxshape;
        b2ShapeProxy circleShape;
        {
            boxshape.count = 4;
            boxshape.radius = 0.0f;
        }

        {
            boxshape.count = 1;
            boxshape.points[0] = b2Vec2(0, 0);
        }
    }

    void PhysicsEngine::Update()
    {
        b2World_Step(myWorld, Time::GetDeltaTime(), substepCount);
    }

    float MyRayCastCallback(b2ShapeId aShape, b2Vec2 aPoint, b2Vec2 aNormal, float aFraction, void* aContext)
    {
        HitResults* myContext = reinterpret_cast<HitResults*>(aContext);

        HitResult& hitContext = myContext->results.emplace_back();

        hitContext.point = { aPoint.x, aPoint.y };
        hitContext.normal = { aNormal.x, aNormal.y };
        hitContext.fraction = aFraction;

        void* userDatat = b2Shape_GetUserData(aShape);
        if (userDatat)
            hitContext.gameobject = reinterpret_cast<ColliderUserData*>(userDatat)->gameobject;

        return aFraction;
    }

    bool MyShapeOverlapCallback(b2ShapeId aShape, void* aContext)
    {
        HitResults* myContext = reinterpret_cast<HitResults*>(aContext);

        HitResult& hitContext = myContext->results.emplace_back();

        void* userDatat = b2Shape_GetUserData(aShape);
        if (userDatat)
            hitContext.gameobject = reinterpret_cast<ColliderUserData*>(userDatat)->gameobject;

        return true;
    }

    bool PhysicsEngine::RayCast(const Ray& aRay, HitResults& aHitResults, float length, Layer aLayerMask)
    {
        b2QueryFilter filter = b2DefaultQueryFilter();

        filter.maskBits = static_cast<uint64_t>(aLayerMask);

        HitResults castContext;
        b2Vec2 translation = b2MulSV(length, b2Normalize(b2Vec2(aRay.direction.x, aRay.direction.y)));
        b2World_CastRay(myWorld, b2Vec2(aRay.position.x, aRay.position.y), translation, filter, MyRayCastCallback, &castContext);

        if (!castContext.results.empty())
        {
            size_t size = sizeof(HitResult) * castContext.results.size();

            aHitResults.results.resize(castContext.results.size());
            std::memcpy(aHitResults.results.data(), castContext.results.data(), size);

            return true;
        }
        return false;
    }

    bool PhysicsEngine::OverlapBox(const Math::Vector2f& aPositon, const Math::Vector2f& aHalfExent, HitResults& aHitResults, Layer aLayerMask)
    {
        b2AABB aabb;
        Math::Vector2f lowerBoundAABB = aPositon - aHalfExent;
        Math::Vector2f upperBoundAABB = aPositon + aHalfExent;
        aabb.lowerBound = b2Vec2(lowerBoundAABB.x, lowerBoundAABB.y);
        aabb.upperBound = b2Vec2(upperBoundAABB.x, upperBoundAABB.y);


        b2QueryFilter filter = b2DefaultQueryFilter();
        filter.maskBits = static_cast<uint64_t>(aLayerMask);
        
        b2World_OverlapAABB(myWorld, aabb, filter, MyShapeOverlapCallback, &aHitResults);
        if (!aHitResults.results.empty())
            return true;

        return false;
    }

    bool PhysicsEngine::OverlapSphere(const Math::Vector2f& aPositon, float aRadius, HitResults& aHitResults, Layer aLayerMask)
    {
        b2Circle circle({ aPositon.x, aPositon.y }, aRadius);
        b2ShapeProxy proxy = b2MakeProxy(&circle.center, 1, circle.radius);

        b2QueryFilter filter = b2DefaultQueryFilter();
        filter.maskBits = static_cast<uint64_t>(aLayerMask);

        b2World_OverlapShape(myWorld, &proxy, filter, MyShapeOverlapCallback, &aHitResults);
        if (!aHitResults.results.empty())
            return true;

        return false;
    }
}