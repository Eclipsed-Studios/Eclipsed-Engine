#include "PhysicsEngine.h"

#include "Timer.h"

#include "box2d/box2d.h"

namespace ENGINE_NAMESPACE
{
#pragma region PhysicsHelperFunctions
    void PhysicsEngine::Physics::SetLinearVelocity(const b2BodyId &aBodyID, const Math::Vector2f &aVelocity)
    {
        b2Vec2 box2DVec2(aVelocity.x, aVelocity.y);
        b2Body_SetLinearVelocity(aBodyID, box2DVec2);
    }
    void PhysicsEngine::Physics::SetAngularVelocity(const b2BodyId &aBodyID, float aVelocity)
    {
        b2Body_SetAngularVelocity(aBodyID, aVelocity);
    }

    Math::Vector2f PhysicsEngine::Physics::GetLinearVelocity(const b2BodyId &aBodyID)
    {
        b2Vec2 velocityB2 = b2Body_GetLinearVelocity(aBodyID);
        return {velocityB2.x, velocityB2.y};
    }
    float PhysicsEngine::Physics::GetAngularVelocity(const b2BodyId &aBodyID)
    {
        float velocity = b2Body_GetAngularVelocity(aBodyID);
        return velocity;
    }

    Math::Vector2f PhysicsEngine::Physics::GetBodyPosition(const b2BodyId &aBodyID)
    {
        b2Vec2 position = b2Body_GetPosition(aBodyID);
        return {position.x, position.y};
    }
    float PhysicsEngine::Physics::GetBodyRotation(const b2BodyId &aBodyID)
    {
        b2Rot rotation = b2Body_GetRotation(aBodyID);
        return b2Rot_GetAngle(rotation);
    }

#pragma endregion

    void PhysicsEngine::RemoveRigidBody(b2BodyId &aBodyID)
    {
        b2DestroyBody(aBodyID);
        aBodyID = b2_nullBodyId;
    }

    void PhysicsEngine::RemoveCollider(b2ShapeId &aShape)
    {
        b2DestroyShape(aShape, false);
    }

    void PhysicsEngine::CreateRigidBody(b2BodyId *aBody, const RigidBodySettings &aBodySettings, const RigidBodyUserData &aData, const Math::Vector2f &aStartPosition)
    {
        b2BodyDef bodyDefine = b2DefaultBodyDef();

        b2MotionLocks motionLocks(aBodySettings.LockXPos, aBodySettings.LockYPos, aBodySettings.LockRotation);
        bodyDefine.motionLocks = motionLocks;

        bodyDefine.type = static_cast<b2BodyType>(aBodySettings.BodyType);
        bodyDefine.position = b2Vec2(aStartPosition.x, aStartPosition.y);

        // bodyDefine.userData = reinterpret_cast(&aData);

        *aBody = b2CreateBody(myWorld, &bodyDefine);
    }

    void PhysicsEngine::CreateBoxCollider(b2ShapeId *aShape, const b2BodyId &aBodyID, const Math::Vector2f &aHalfExtents)
    {
        b2Polygon polygon = b2MakeBox(aHalfExtents.x, aHalfExtents.y);
        b2ShapeDef groundShapeDef = b2DefaultShapeDef();
        *aShape = b2CreatePolygonShape(aBodyID, &groundShapeDef, &polygon);
    }

    void PhysicsEngine::Init()
    {
        b2WorldDef worldDef;
        worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2(myGravity.x, myGravity.y);
        myWorld = b2CreateWorld(&worldDef);
    }

    void PhysicsEngine::Update()
    {
        b2World_Step(myWorld, Time::GetDeltaTime(), substepCount);
    }
}