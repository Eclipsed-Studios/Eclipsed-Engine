#pragma once

#include "Components/Base/Component.h"

#include "PlayerStateMachine.h"

#include "BitMask.hpp"

namespace Eclipse
{
	enum PlayerBitmaskIndex {
		Walking, Running, Jumping, Attacking
	};


	class Player : public Component
	{
		friend class PlayerController;

	private:
		enum States : int
		{
			Walking, Running, Jump,
			Attacking, Climbing,
			Walking_And_Attacking,
			Duck, 

			Idle
		};

	public:
		BASE_SELECTION(Player, 5)

		void Awake() override;
		void Update() override;

	private:
		void CheckInput();

		void HandleInput();

		void HandleMovement();
		void HandleIdle();
		void HandleJump();
		void HandleAttack();
		void HandleDuck();

	private:
		States myState = States::Idle;

		int myMoveDirection = 0;
		Utilities::BitMask<> myInput;

		float myTimer = 0.f;
		const float Jump_Duration = 0.4f;
		const float Attack_Duration = 0.2f;

	private:
		class Transform2D* myTransform = nullptr;
		class SpriteRenderer2D* mySpriteRenderer = nullptr;
		class SpriteSheetAnimator2D* myAnimation = nullptr;
	};
}