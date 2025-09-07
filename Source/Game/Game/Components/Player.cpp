#include "Player.h"

#include "Input/InputMapper.h"
#include "Input/Input.h"

#include "ECS/ComponentManager.h"

#include "Components/Physics/RigidBody2D.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/Transform2D.h"

#include "Timer.h"

namespace ENGINE_NAMESPACE
{
	void Player::Awake()
	{
		myTransform = GetComp(Transform2D, gameObject);
		mySpriteRenderer = GetComp(SpriteRenderer2D, gameObject);
		myAnimation = GetComp(SpriteSheetAnimator2D, gameObject);

		myAnimation->Play();
	}

	void Player::Update()
	{
		CheckInput();
		HandleInput();

		myTimer -= Time::GetDeltaTime();

		if (myMoveDirection != 0)
		{
			mySpriteRenderer->SetXMirror(myMoveDirection < 0);
		}
	}

	void Player::CheckInput()
	{
		myMoveDirection = InputMapper::ReadValue("Sides");
	}



	void Player::HandleInput()
	{
		switch (myState)
		{
		case Player::Walking:
		case Player::Running:
			HandleMovement();
			break;
		case Player::Jump:
			HandleJump();
			break;
		case Player::Idle:
			HandleIdle();
			break;

		case Player::Attacking:
			HandleAttack();
			break;

		case Player::Duck:
			HandleDuck();
			break;
		}
	}
	void Player::HandleMovement()
	{
		if (myMoveDirection == 0)
		{
			myState = States::Idle;
			return;
		}

		switch (myState)
		{
		case Player::Walking:
			myAnimation->SetCurrentAnimation("Walking");
			break;
		case Player::Running:
			myAnimation->SetCurrentAnimation("Running");
			break;
		}

		if (Input::GetMouseDown(MouseButton::LEFT))
		{
			myTimer = Attack_Duration;
			myState = States::Attacking;
		}
		else if (InputMapper::ReadValue("Jump"))
		{
			myTimer = Jump_Duration;
			myState = States::Jump;
		}
	}
	void Player::HandleIdle()
	{
		myAnimation->SetCurrentAnimation("Idle");

		if (InputMapper::ReadValue("Duck"))
		{
			myState = States::Duck;
			return;
		}

		if (Input::GetMouseDown(MouseButton::LEFT))
		{
			myTimer = Attack_Duration;
			myState = States::Attacking;
		}
		else if (InputMapper::ReadValue("Jump"))
		{
			myTimer = Jump_Duration;
			myState = States::Jump;
		}
		else if (myMoveDirection != 0)
		{
			if (Input::GetKey(Keycode::L_SHIFT))
			{
				myState = States::Running;
			}
			else
			{
				myState = States::Walking;
			}
		}
	}
	void Player::HandleJump()
	{
		myAnimation->SetCurrentAnimation("Jump");

		if (Input::GetMouseDown(MouseButton::LEFT))
		{
			myTimer = Attack_Duration;
			myState = States::Attacking;
			return;
		}

		if (myTimer <= 0.f)
		{
			myState = States::Idle;
		}
	}

	void Player::HandleAttack()
	{
		myAnimation->SetCurrentAnimation("Attack");

		if (myTimer <= 0.f)
		{
			myState = States::Idle;
		}
	}

	void Player::HandleDuck()
	{
		myAnimation->SetCurrentAnimation("Duck");

		if (InputMapper::ReadValue("Duck")) myState = States::Duck;
		else myState = States::Idle;
	}
}
