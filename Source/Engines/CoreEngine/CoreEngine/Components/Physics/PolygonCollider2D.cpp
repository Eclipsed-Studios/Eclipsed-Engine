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
        RigidBody2D* rigidBody = ComponentManager::GetComponent<RigidBody2D>(gameObject);

        if (!rigidBody)
        {
            myUserData = { gameObject };
            PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, RigidBodySettings(), ComponentManager::GetComponent<Transform2D>(gameObject)->GetPosition());
        }
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreatePolygonCollider(&myInternalCollider, myBodyRef, myPoints, myLayer);

        myTransform = ComponentManager::GetComponent<Transform2D>(gameObject);
        myTransform->AddFunctionToRunOnDirtyUpdate([this]() { this->OnTransformDirty(); });
    }

    void PolygonCollider2D::AddPoint(const Math::Vector2f& aPoint)
    {
        Transform2D* transform = ComponentManager::GetComponent<Transform2D>(gameObject);
        Math::Vector2f scale = (Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.01f);

        scale *= aPoint * Math::Vector2f(2.f, 2.f) - Math::Vector2f(1.f, 1.f);

        myPoints.emplace_back(scale);
    }

    void PolygonCollider2D::OnTransformDirty()
    {
        Math::Vector2f scale = Math::Vector2f(myTransform->GetScale().x * 0.5f, myTransform->GetScale().y) * 0.01f;

        PhysicsEngine::SetTransformPolygon(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), myPoints, scale);
    }

    void PolygonCollider2D::DrawInspector()
    {
    }
}