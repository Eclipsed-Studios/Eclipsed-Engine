#include "RigidBody2D.h"

#include "../PhysicsEngine/PhysicsEngine.h"

#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

namespace ENGINE_NAMESPACE
{
    typedef PhysicsEngine::Physics PhysHelper;

    RigidBody2D::~RigidBody2D()
    {

    }

    void RigidBody2D::Awake()
    {
        myRigidBodySettings.BodyType = DynamicBody;

        myTransform = ComponentManager::GetComponent<Transform2D>(gameObject);
        mySavedDataForUserData = RigidBodyUserData(gameObject);

        const Math::Vector2f &startPosition = myTransform->GetPosition();
        PhysicsEngine::CreateRigidBody(&myBody, myRigidBodySettings, mySavedDataForUserData, startPosition);
        bodyHasBeenCreated = true;
    }

    void RigidBody2D::EarlyUpdate()
    {
        myVelocity = PhysHelper::GetLinearVelocity(myBody);
        myAngularVelocity = PhysHelper::GetAngularVelocity(myBody);

        Math::Vector2f position = PhysHelper::GetBodyPosition(myBody);
        myTransform->SetPosition(position);
        float rotation = PhysHelper::GetBodyRotation(myBody);
        myTransform->SetRotation(rotation);
    }

    void RigidBody2D::SetVelocity(const Math::Vector2f &aVelocity)
    {
        myVelocity = aVelocity;
        PhysHelper::SetLinearVelocity(myBody, myVelocity);
    }

    void RigidBody2D::AddForce(const Math::Vector2f &aVelocity)
    {
        SetVelocity(myVelocity + aVelocity);
    }

    const Math::Vector2f &RigidBody2D::GetVelocity()
    {
        return myVelocity;
    }

    void RigidBody2D::SetAngularVelocity(float aAngularVelocity)
    {
        myAngularVelocity = aAngularVelocity;
        PhysHelper::SetAngularVelocity(myBody, aAngularVelocity);
    }

    const float RigidBody2D::GetAngularVelocity()
    {
        return myAngularVelocity;
    }

    void RigidBody2D::SetRotationLocked(bool aValue)
    {
        myRigidBodySettings.LockRotation = aValue;
    }
    bool RigidBody2D::GetRotationLocked()
    {
        return myRigidBodySettings.LockRotation;
    }

    void RigidBody2D::SetXPosLocked(bool aValue)
    {
        myRigidBodySettings.LockXPos = aValue;
    }
    bool RigidBody2D::GetXPosLocked()
    {
        return myRigidBodySettings.LockXPos;
    }

    void RigidBody2D::SetYPosLocked(bool aValue)
    {
        myRigidBodySettings.LockYPos = aValue;
    }
    bool RigidBody2D::GetYPosLocked()
    {
        return myRigidBodySettings.LockYPos;
    }
}