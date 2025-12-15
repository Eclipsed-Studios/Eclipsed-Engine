#include "Collider2D.h"

#include "RigidBody2D.h"

#include "EntityEngine/ComponentManager.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "EntityEngine/Components/Transform2D.h"

namespace Eclipse
{
    void Collider2D::OnDestroy()
    {
        auto rigidBody = gameObject->GetComponent<RigidBody2D>();
        if (!BodyCreatedByRB)
        {
            PhysicsEngine::DeleteShape(&myInternalCollider);
            PhysicsEngine::DeleteBody(&myBodyRef);
        }
        else if (rigidBody)
        {
            PhysicsEngine::DeleteShape(&myInternalCollider);
        }

        myCreatedInternally = false;
    }

    void Collider2D::OnComponentAdded()
    {
        OnSceneLoaded();
    }

    void Collider2D::OnSceneLoaded()
    {
        if (!myCreatedInternally)
        {
            myTransform = gameObject->transform;

            myLastLayer = static_cast<int>(myLayer->value);

            RigidBody2D* rigidBody = gameObject->GetComponent<RigidBody2D>();
            if (!rigidBody)
            {
                myUserData = { gameObject->GetID() };
                PhysicsEngine::CreateRigidBody(&myBodyRef, &myUserData, StaticBody, false, false, false, myTransform->GetPosition());
            }
            else
            {
                BodyCreatedByRB = true;
                myBodyRef = rigidBody->myBody;
            }

            myCreatedInternally = true;

            myTransform->AddFunctionToRunOnDirtyUpdate([this]() {
                this->OnTransformDirty();
                });

            CreateCollider();
        }
    }

    void Collider2D::EditorUpdate()
    {
        DeltaChanges();

        if (myLastLayer != static_cast<int>(myLayer->value))
        {
            myLastLayer = myLayer->value;
            PhysicsEngine::ChangeLayer(myInternalCollider, myLayer);
        }
    }
}