#include "BoxCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    void BoxCollider2D::Awake()
    {
        RigidBody2D* rigidBody = ComponentManager::GetComponent<RigidBody2D>(gameObject);

        if (!rigidBody)
            PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, RigidBodySettings(), ComponentManager::GetComponent<Transform2D>(gameObject)->GetPosition());
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreateBoxCollider(&myInternalCollider, myBodyRef, myHalfExtents, myLayer);
    }

    void BoxCollider2D::SetScale(const Math::Vector2f& aHalfExtents)
    {
        auto& temporary = TemporarySettingsSingleton::Get();

        float oneDivX = temporary.GetOneDivResolutionX();
        float oneDivY = temporary.GetOneDivResolutionY();

        Transform2D* transform = ComponentManager::GetComponent<Transform2D>(gameObject);

        Math::Vector2f halfExtent = Math::Vector2f(transform->GetScale().x * oneDivY, transform->GetScale().y * oneDivY);

        halfExtent.x *= aHalfExtents.x;
        halfExtent.y *= aHalfExtents.y;

        myHalfExtents = halfExtent;
    }
}