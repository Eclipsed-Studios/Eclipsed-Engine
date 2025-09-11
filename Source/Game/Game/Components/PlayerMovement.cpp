#include "PlayerMovement.h"

#include "ECS/ComponentManager.h"

#include "Components/Physics/RigidBody2D.h"
#include "Components/Player.h"
#include "Components/Transform2D.h"

#include "PhysicsEngine.h"
#include "Input/InputMapper.h"

namespace ENGINE_NAMESPACE
{
	void PlayerMovement::Awake()
	{
		myRigidBody = GetComp(RigidBody2D, gameObject);
		myTransform = GetComp(Transform2D, gameObject);
		myPlayer = GetComp(Player, gameObject);
	}

	void PlayerMovement::Update()
	{
		if (!myPlayer) return;

		if (myPlayer->myState == Player::States::Duck) return;

		const int moveDirection = myPlayer->myMoveDirection;

		if (moveDirection != 0)
		{
			float velY = myRigidBody->GetVelocity().Y;
			myRigidBody->SetVelocity({ moveDirection * myMovementSpeed, velY });
		}

		HitResults hit;
		bool isGrounded = PhysicsEngine::OverlapSphere(myTransform->GetPosition() - Math::Vector2f(0.f, 0.07), 0.05f, hit, Layer::Ground);
		if (isGrounded)
		{
			if (myPlayer->myState == Player::States::Jump && InputMapper::ReadValue("Jump"))
			{
				float velX = myRigidBody->GetVelocity().x;
				myRigidBody->SetVelocity({ velX, myJumpStrength });
			}
		}
	}
}