#include "CapsuleCollider2D.h"

#include "PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#undef max

namespace Eclipse
{
    void CapsuleCollider2D::CreateCollider()
    {
        PhysicsEngine::CreateCapsuleCollider(&myInternalCollider, myBodyRef, myInternalRadius, myInternalHalfHeight, myLayer);
    }

    void CapsuleCollider2D::SetRadius(float aRadius)
    {
        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f size = Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.01f;

        Radius = aRadius;
        myInternalRadius = Radius * std::max(size.x, size.y);
    }

    void CapsuleCollider2D::SetHalfHeight(float aHalfHeight)
    {
        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f size = Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.01f;

        HalfHeight = aHalfHeight;
        myInternalHalfHeight = HalfHeight * size.y;
    }

    void CapsuleCollider2D::OnTransformDirty()
    {
        Math::Vector2f size = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        float radius = Radius * std::max(size.x, size.y);
        float halfHeight = HalfHeight * size.y;

        PhysicsEngine::SetTransformCapsule(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), radius, halfHeight);
    }
}