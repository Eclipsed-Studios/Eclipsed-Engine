#include "RigidBody2D.h"

#include "../PhysicsEngine/PhysicsEngine.h"
#include "box2d/box2d.h"

#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

namespace ENGINE_NAMESPACE
{
    void RigidBody2D::Awake()
    {
        myTransform = ComponentManager::GetComponent<Transform2D>(gameObject);

        myBodyID = PhysicsEngine::CreateRigidBody();
    }

    void RigidBody2D::EarlyUpdate()
    {
        b2Vec2 velocityB2 = b2Body_GetLinearVelocity(*myBodyID);
        myVelocity = {velocityB2.x, velocityB2.y};

        b2Vec2 position = b2Body_GetPosition(*myBodyID);
        b2Rot rotation = b2Body_GetRotation(*myBodyID);

        myTransform->SetPosition(position.x, position.y);
        myTransform->SetRotation(b2Rot_GetAngle(rotation));
    }

    void RigidBody2D::SetVelocity(const Math::Vector2f &aVelocity)
    {
        myVelocity = aVelocity;
        b2Vec2 vel = {myVelocity.x, myVelocity.y};
        b2Body_SetLinearVelocity(*myBodyID, vel);
    }

    void RigidBody2D::AddForce(const Math::Vector2f &aVelocity)
    {
        myVelocity += aVelocity;
        b2Vec2 vel = {myVelocity.x, myVelocity.y};
        b2Body_SetLinearVelocity(*myBodyID, vel);
    }

    const Math::Vector2f &RigidBody2D::GetVelocity()
    {
        return myVelocity;
    }

    void RigidBody2D::SetAngularVelocity(float aAngularVelocity)
    {
        myAngularVelocity = aAngularVelocity;
    }

    const float RigidBody2D::GetAngularVelocity()
    {
        return myAngularVelocity;
    }
}