#include "BoxCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"

#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "TemporarySettingsSingleton.h"

namespace Eclipse
{
    void BoxCollider2D::EditorUpdate()
    {
        if (myLastHalfExtents.x != HalfExtents->x || myLastHalfExtents.y != HalfExtents->y)
        {
            OnTransformDirty();
        }

        if (myLastColliderPivot.x != ColliderPivot->x || myLastColliderPivot.y != ColliderPivot->y)
        {
            OnTransformDirty();
        }

        if (myLastLayer != static_cast<int>(myLayer->value))
        {
            myLastLayer = myLayer->value;
            PhysicsEngine::ChangeLayer(myInternalCollider, myLayer);
        }
    }

    void BoxCollider2D::OnComponentAdded()
    {
        OnSceneLoaded();
    }

    void BoxCollider2D::OnSceneLoaded()
    {
        if (!myCreatedInternally)
        {
            myLastLayer = static_cast<int>(myLayer->value);

            myTransform = gameObject->transform;
            SetScale(HalfExtents);

            RigidBody2D* rigidBody = gameObject->GetComponent<RigidBody2D>();
            if (!rigidBody)
            {
                myUserData = { gameObject->GetID() };
                PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, StaticBody, false, false, false, gameObject->GetComponent<Transform2D>()->GetPosition());
            }
            else
                myBodyRef = rigidBody->myBody;

            PhysicsEngine::CreateBoxCollider(&myInternalCollider, myBodyRef, myHalfExtents, myLayer);

            myTransform->AddFunctionToRunOnDirtyUpdate([this]() {
                this->OnTransformDirty();
                });

            myCreatedInternally = true;
        }
    }

    void BoxCollider2D::SetScale(const Math::Vector2f& aHalfExtents)
    {
        myLastHalfExtents = HalfExtents;
        HalfExtents = aHalfExtents;

        Math::Vector2f halfExtent = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        halfExtent.x *= aHalfExtents.x;
        halfExtent.y *= aHalfExtents.y;

        myHalfExtents = halfExtent;
    }

    void BoxCollider2D::OnTransformDirty()
    {
        myLastHalfExtents = HalfExtents;
        myLastColliderPivot = ColliderPivot;

        Math::Vector2f halfExtent = Math::Vector2f(myTransform->GetScale().x, myTransform->GetScale().y) * 0.01f;

        halfExtent.x *= HalfExtents->x;
        halfExtent.y *= HalfExtents->y;

        myHalfExtents = halfExtent;

        PhysicsEngine::SetTransformBox(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation(), myHalfExtents, { ColliderPivot->x * halfExtent.x * 2.f, ColliderPivot->y * halfExtent.y * 2.f });
    }
}