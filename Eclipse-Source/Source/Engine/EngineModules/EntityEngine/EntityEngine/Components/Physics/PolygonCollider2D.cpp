#include "PolygonCollider2D.h"

#include "PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "EntityEngine/Components/Transform2D.h"

#include "EntityEngine/ComponentManager.h"

#include "EntityEngine/Components/Rendering/SpriteRenderer2D.h"
//#include "AssetManagement/Resources/Texture.h"

namespace Eclipse
{
    void PolygonCollider2D::CreateCollider()
    {
        PhysicsEngine::CreatePolygonCollider(&myInternalCollider, myBodyRef, myPoints, myLayer);
    }

    void PolygonCollider2D::AddPoint(const Math::Vector2f& aPoint)
    {
        Transform2D* transform = gameObject->GetComponent<Transform2D>();
        Math::Vector2f scale = (Math::Vector2f(transform->GetScale().x, transform->GetScale().y) * 0.1f);

        scale *= aPoint * Math::Vector2f(2.f, 2.f) - Math::Vector2f(1.f, 1.f);

        myPoints->emplace_back(scale);
    }

    void PolygonCollider2D::DeltaChanges()
    {
        if (myLastPoints.empty() || memcmp(&myPoints->data()->x, &myLastPoints.data()->x, myPoints->size() * sizeof(Math::Vector2f)))
        {
            myLastPoints.resize(myPoints->size());
            memcpy(&myLastPoints.data()->x, &myPoints->data()->x, myPoints->size() * sizeof(Math::Vector2f));

            OnTransformDirty();
        }
    }
    
    void PolygonCollider2D::OnTransformDirty()
    {
        Math::Vector2f scale = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        PhysicsEngine::SetTransformPolygon(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), myPoints, scale);
    }
}