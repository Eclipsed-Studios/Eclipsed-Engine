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

    void PhysicsEngine::CreateRigidBody(b2BodyId* aBody, UserData* aUserData, const RigidBodySettings& aBodySettings, const Math::Vector2f& aStartPosition)
    {
        b2BodyDef bodyDefine = b2DefaultBodyDef();

        b2MotionLocks motionLocks(aBodySettings.LockXPos, aBodySettings.LockYPos, aBodySettings.LockRotation);
        bodyDefine.motionLocks = motionLocks;

        bodyDefine.type = static_cast<b2BodyType>(aBodySettings.BodyType);
        bodyDefine.position = b2Vec2(aStartPosition.x, aStartPosition.y);

        //bodyDefine.linearDamping = 5.f;

        bodyDefine.userData = aUserData;

        *aBody = b2CreateBody(myWorld, &bodyDefine);
    }

    void PhysicsEngine::CreateBoxCollider(b2ShapeId* aShape, const b2BodyId& aBodyID, const Math::Vector2f& aHalfExtents, Layer aLayer)
    {
        b2Polygon polygon = b2MakeBox(aHalfExtents.x, aHalfExtents.y);
        b2ShapeDef shapeDef = b2DefaultShapeDef();

        shapeDef.enableHitEvents = true;
        shapeDef.enableContactEvents = true;

        shapeDef.filter.categoryBits = static_cast<uint64_t>(aLayer);

        *aShape = b2CreatePolygonShape(aBodyID, &shapeDef, &polygon);
    }

    void PhysicsEngine::Init(int aSubstepCount, const Math::Vector2f& aGravity)
    {
        mySubstepCount = aSubstepCount;
        myGravity = aGravity;

        b2WorldDef worldDef;
        worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2(myGravity.x, myGravity.y);
        
        myWorld = b2CreateWorld(&worldDef);
    }

    void PhysicsEngine::Update()
    {
        b2World_Step(myWorld, Time::GetDeltaTime(), mySubstepCount);

        CheckCollisions();
    }

    void HandleBeginContacts(b2ContactBeginTouchEvent& aEvent)
    {
        const b2ShapeId shapeIdA = aEvent.shapeIdA;
        const b2ShapeId shapeIdB = aEvent.shapeIdB;

        const b2BodyId bodyIdA = b2Shape_GetBody(shapeIdA);
        const b2BodyId bodyIdB = b2Shape_GetBody(shapeIdB);

        void* userInternalDataA = b2Body_GetUserData(bodyIdA);
        void* userInternalDataB = b2Body_GetUserData(bodyIdB);

        UserData userDataA = *reinterpret_cast<UserData*>(userInternalDataA);
        UserData userDataB = *reinterpret_cast<UserData*>(userInternalDataB);

        PhysicsEngine::myBeginContactCallback(userDataA);
        PhysicsEngine::myBeginContactCallback(userDataB);
    }

    void HandleEndContacts(b2ContactEndTouchEvent& aEvent)
    {
        const b2ShapeId shapeIdA = aEvent.shapeIdA;
        const b2ShapeId shapeIdB = aEvent.shapeIdB;

        const b2BodyId bodyIdA = b2Shape_GetBody(shapeIdA);
        const b2BodyId bodyIdB = b2Shape_GetBody(shapeIdB);

        void* userInternalDataA = b2Body_GetUserData(bodyIdA);
        void* userInternalDataB = b2Body_GetUserData(bodyIdB);

        UserData userDataA = *reinterpret_cast<UserData*>(userInternalDataA);
        UserData userDataB = *reinterpret_cast<UserData*>(userInternalDataB);

        PhysicsEngine::myEndContactCallback(userDataA);
        PhysicsEngine::myEndContactCallback(userDataB);
    }

    void PhysicsEngine::CheckCollisions()
    {
        b2ContactEvents contactEvents = b2World_GetContactEvents(myWorld);

        for (int i = 0; i < contactEvents.beginCount; ++i)
        {
            b2ContactBeginTouchEvent event = contactEvents.beginEvents[i];
            HandleBeginContacts(event);
        }
        // for (int i = 0; i < contactEvents.hitCount; ++i)
        // {
        //     b2ContactBeginTouchEvent event = contactEvents.beginEvents[i];
        //     HandleBeginContacts(event);
        // }
        for (int i = 0; i < contactEvents.endCount; ++i)
        {
            b2ContactEndTouchEvent event = contactEvents.endEvents[i];
            HandleEndContacts(event);
        }
    }

    float MyRayCastCallback(b2ShapeId aShape, b2Vec2 aPoint, b2Vec2 aNormal, float aFraction, void* aContext)
    {
        HitResults* myContext = reinterpret_cast<HitResults*>(aContext);

        HitResult& hitContext = myContext->results.emplace_back();

        hitContext.point = { aPoint.x, aPoint.y };
        hitContext.normal = { aNormal.x, aNormal.y };
        hitContext.fraction = aFraction;

        const b2BodyId bodyIdA = b2Shape_GetBody(aShape);
        void* userData = b2Body_GetUserData(bodyIdA);

        if (userData)
            hitContext.gameobject = reinterpret_cast<UserData*>(userData)->gameobject;

        return aFraction;
    }

    bool MyShapeOverlapCallback(b2ShapeId aShape, void* aContext)
    {
        HitResults* myContext = reinterpret_cast<HitResults*>(aContext);

        HitResult& hitContext = myContext->results.emplace_back();

        const b2BodyId bodyIdA = b2Shape_GetBody(aShape);
        void* userData = b2Body_GetUserData(bodyIdA);

        if (userData)
            hitContext.gameobject = reinterpret_cast<UserData*>(userData)->gameobject;

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