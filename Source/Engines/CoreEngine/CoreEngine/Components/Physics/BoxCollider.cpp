#include "BoxCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "TemporarySettingsSingleton.h"

namespace Eclipse
{
    void BoxCollider2D::Awake()
    {
        RigidBody2D* rigidBody = gameObject->GetComponent<RigidBody2D>();

        if (!rigidBody)
        {
            myUserData = { gameObject->GetID() };
            PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, RigidBodySettings(), gameObject->GetComponent<Transform2D>()->GetPosition());
        }
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreateBoxCollider(&myInternalCollider, myBodyRef, myHalfExtents, myLayer);

        myTransform = gameObject->GetComponent<Transform2D>();
        myTransform->AddFunctionToRunOnDirtyUpdate([this]() { this->OnTransformDirty(); });
    }

    void BoxCollider2D::SetScale(const Math::Vector2f& aHalfExtents)
    {
        myScale = aHalfExtents;

        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f halfExtent = Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.01f;

        halfExtent.x *= aHalfExtents.x;
        halfExtent.y *= aHalfExtents.y;

        myHalfExtents = halfExtent;
    }

    void BoxCollider2D::DrawInspector()
    {
    }

    void BoxCollider2D::OnTransformDirty()
    {
        Math::Vector2f halfExtent = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        halfExtent.x *= myScale.x;
        halfExtent.y *= myScale.y;

        myHalfExtents = halfExtent;

        PhysicsEngine::SetTransformBox(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), myHalfExtents);
    }
}