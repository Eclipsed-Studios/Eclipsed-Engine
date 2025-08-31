#include "BoxCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    void BoxCollider2D::Start()
    {
        RigidBody2D *rigidBody = ComponentManager::GetComponent<RigidBody2D>(gameObject);

        if (!rigidBody)
            PhysicsEngine::CreateRigidBody(&myBodyRef, RigidBodySettings(), RigidBodyUserData(gameObject), ComponentManager::GetComponent<Transform2D>(gameObject)->GetPosition());
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreateBoxCollider(&myInternalCollider, myBodyRef, myHalfExtents);
    }

    void BoxCollider2D::SetHalfExtents(const Math::Vector2f &aHalfExtents)
    {
        auto &temporary = TemporarySettingsSingleton::Get();

        float oneDivX = temporary.GetOneDivResolutionX();
        float oneDivY = temporary.GetOneDivResolutionY();

        Transform2D *transform = ComponentManager::GetComponent<Transform2D>(gameObject);

        Math::Vector2f halfExtent = Math::Vector2f(aHalfExtents.x * oneDivY, aHalfExtents.y * oneDivY);

        halfExtent.x *= 2.f;
        halfExtent.y *= 2.f;

        // halfExtent.x *= transform->GetScale().x * oneDivX;
        // halfExtent.y *= transform->GetScale().y * oneDivY;

        myHalfExtents = halfExtent;
    }
}