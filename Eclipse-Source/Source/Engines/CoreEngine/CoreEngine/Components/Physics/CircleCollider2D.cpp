#include "CircleCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#undef max

namespace Eclipse
{
    void CircleCollider2D::Awake()
    {
        RigidBody2D* rigidBody = gameObject->GetComponent<RigidBody2D>();

        if (!rigidBody)
        {
            myUserData = { gameObject->GetID() };
            PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, RigidBodySettings(), gameObject->GetComponent<Transform2D>()->GetPosition());
        }
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreateCircleCollider(&myInternalCollider, myBodyRef, myRadius, myLayer);

        myTransform = gameObject->GetComponent<Transform2D>();
        myTransform->AddFunctionToRunOnDirtyUpdate([this]() { this->OnTransformDirty(); });
    }

    void CircleCollider2D::SetRadius(float aRadius)
    {
        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f size = Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.01f;

        myRealRadius = aRadius;
        myRadius = myRealRadius * std::max(size.x, size.y);
    }

    void CircleCollider2D::DrawInspector()
    {
    }

    void CircleCollider2D::OnTransformDirty()
    {
        Math::Vector2f size = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        float radius = myRealRadius * std::max(size.x, size.y);

        PhysicsEngine::SetTransformCircle(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), radius);
    }
}