#include "Collider2D.h"

#include "RigidBody2D.h"

#include "EntityEngine/ComponentManager.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "EclipsedEngine/Components/Transform2D.h"

namespace Eclipse
{
    void Collider2D::OnDestroy()
    {
        if (BodyOwned)
        {
            PhysicsEngine::Get().DeleteShape(myInternalCollider);

            std::vector<Collider2D*> colliders;
            ComponentManager::GetAllComponentsOfType<Collider2D>(gameObject->GetID(), colliders);

            if (!colliders.size())
                PhysicsEngine::Get().DeleteBody(myBodyRef);
        }
        else
        {
            PhysicsEngine::Get().DeleteShape(myInternalCollider);
        }
    }

    void Collider2D::OnComponentAdded()
    {
        myTransform = gameObject->transform;
        myLastLayer = static_cast<int>(myLayer->value);

        myUserData = { gameObject->GetID() };

        std::vector<Collider2D*> colliders;
        ComponentManager::GetAllComponentsOfType<Collider2D>(gameObject->GetID(), colliders);

        bool ColliderHasRB = false;

        for (auto& collider : colliders)
        {
            if (collider->BodyOwned)
            {
                myBodyRef = collider->myBodyRef;
                ColliderHasRB = true;
                break;
            }
        }

        if (!ColliderHasRB)
        {
            PhysicsEngine::Get().CreateRigidBody(myBodyRef, &myUserData, StaticBody, false, false, false, myTransform->GetPosition());
            BodyOwned = true;
        }

        myTransform->AddFunctionToRunOnDirtyUpdate(this, [this]() {
            this->OnTransformDirty();
            });

        CreateCollider();

        PhysicsEngine::Get().SetPhysicsMaterial(myInternalCollider, physMaterial);
    }

    void Collider2D::EditorUpdate()
    {
        DeltaChanges();

        if (myLastLayer != static_cast<int>(myLayer->value))
        {
            myLastLayer = myLayer->value;
            PhysicsEngine::Get().ChangeLayer(myInternalCollider, myLayer);
        }
    }

    void Collider2D::OnTransformDirty()
    {
        if (BodyOwnedByRB)
            return;

        PhysicsEngine::Get().SetTransform(myBodyRef, myTransform->GetPosition(), myTransform->GetRotation());
        OnShapeDirty();
    }
}