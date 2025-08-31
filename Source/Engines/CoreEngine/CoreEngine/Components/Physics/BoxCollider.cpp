#include "BoxCollider2D.h"

#include "../Engines/PhysicsEngine/PhysicsEngine.h"

#include "RigidBody2D.h"
#include "Components/Transform2D.h"

#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
    void BoxCollider2D::Start()
    {
        RigidBody2D *rigidBody = ComponentManager::GetComponent<RigidBody2D>(gameObject);

        if (!rigidBody)
            PhysicsEngine::CreateRigidBody(&myBodyRef, RigidBodySettings(), RigidBodyUserData(gameObject, 0), ComponentManager::GetComponent<Transform2D>(gameObject)->GetPosition());
        else
            myBodyRef = rigidBody->myBody;

        PhysicsEngine::CreateBoxCollider(&myInternalCollider, myBodyRef, myHalfExtents);
    }

    void BoxCollider2D::SetHalfExtents(const Math::Vector2f &aHalfExtents)
    {
        myHalfExtents = aHalfExtents * 0.5f;
    }
}