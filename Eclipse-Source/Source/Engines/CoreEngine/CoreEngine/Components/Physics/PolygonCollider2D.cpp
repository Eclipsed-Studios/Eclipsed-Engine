#include "PolygonCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "TemporarySettingsSingleton.h"

#include "Components/Rendering/SpriteRenderer2D.h"
#include "AssetManagement/Resources/Texture.h"

namespace Eclipse
{
    void PolygonCollider2D::Awake()
    {
        myTransform = gameObject->GetComponent<Transform2D>();
        myTransform->AddFunctionToRunOnDirtyUpdate([this]() { this->OnTransformDirty(); });

        RigidBody2D* rigidBody = gameObject->GetComponent<RigidBody2D>();

        if (!rigidBody)
        {
            myUserData = { gameObject->GetID() };
            PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, StaticBody, false, false, false, gameObject->GetComponent<Transform2D>()->GetPosition());
        }
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreatePolygonCollider(&myInternalCollider, myBodyRef, myPoints, myLayer);

        OnTransformDirty();
    }

    void PolygonCollider2D::AddPoint(const Math::Vector2f& aPoint)
    {
        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f scale = (Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.1f);

        scale *= aPoint * Math::Vector2f(2.f, 2.f) - Math::Vector2f(1.f, 1.f);

        myPoints->emplace_back(scale);
    }

    void PolygonCollider2D::OnTransformDirty()
    {
        Math::Vector2f scale = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        PhysicsEngine::SetTransformPolygon(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), myPoints, scale);
    }
}