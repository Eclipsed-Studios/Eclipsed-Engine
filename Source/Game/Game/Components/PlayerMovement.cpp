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

		myAnimation->Play();
		if (directionMove)
		{
			if (!myIsJumping)
			{
				myAnimation->SetCurrentAnimation("Running");
			}

			float velY = myRigidBody->GetVelocity().Y;
			float time = Time::GetDeltaTime();
			myRigidBody->SetVelocity({ directionMove * myMoveSpeed * 1, velY });

			if (directionMove > 0)
				mySpriteRenderer->SetXMirror(false);
			else
				mySpriteRenderer->SetXMirror(true);
		}
		else if (myIsJumping)
		{
			myAnimation->SetCurrentAnimation("Jump");
		}
		else
		{
			myAnimation->SetCurrentAnimation("Idle");
		}


		HitResults hit;
		bool isGrounded = PhysicsEngine::OverlapSphere(myTransform->GetPosition() - Math::Vector2f(0.f, 0.07), 0.03f, hit, Layer::Ground);

		if (isGrounded)
		{
			if (myIsJumping && myRigidBody->GetVelocity().y <= 0.f)
			{
				myIsJumping = false;

			}

			if (InputMapper::ReadValue("Jump"))
			{
				float velX = myRigidBody->GetVelocity().x;
				myRigidBody->SetVelocity({ velX, myJumpStrength });

				myIsJumping = true;
			}
		}
	}

	void PlayerMovement::Awake()
	{
		myRigidBody = GetComp(RigidBody2D, gameObject);
		myTransform = GetComp(Transform2D, gameObject);
		mySpriteRenderer = GetComp(SpriteRendrer2D, gameObject);
		myAnimation = GetComp(SpriteSheetAnimator2D, gameObject);
	}
}