#include "PlayerMovement.h"

#include "ECS/ComponentManager.h"

#include "Components/Physics/RigidBody2D.h"
#include "Components/Rendering/SpriteRendrer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/Transform2D.h"

#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"
#include "Input/InputMapper.h"

#include "Timer.h"

namespace ENGINE_NAMESPACE
{
    void PlayerMovement::Update()
    {
        float directionMove = InputMapper::ReadValue("Sides");

        if (directionMove)
        {
            myAnimation->Play();

            float moveSpeed = 1;
            float velY = myRigidBody->GetVelocity().Y;
            float time = Time::GetDeltaTime();
            myRigidBody->SetVelocity({ directionMove * moveSpeed * 1, velY });

            if (directionMove > 0)
                mySpriteRenderer->SetXMirror(false);
            else
                mySpriteRenderer->SetXMirror(true);
        }
        else
        {
            myAnimation->Pause();
        }

        if (InputMapper::ReadValue("Jump"))
        {
            HitResults hit;
            if (PhysicsEngine::OverlapSphere(myTransform->GetPosition() - Math::Vector2f(0.f, 0.07), 0.1f, hit, Layer::Ground))
            {
                float velX = myRigidBody->GetVelocity().x;
                myRigidBody->SetVelocity({ velX, 4.f });
            }
        }
    }

    void PlayerMovement::Awake()
    {
        myRigidBody = GetComp(RigidBody2D, 1);
        myTransform = GetComp(Transform2D, 1);
        mySpriteRenderer = GetComp(SpriteRendrer2D, 1);
        myAnimation = GetComp(Animation2D, 1);
    }
}