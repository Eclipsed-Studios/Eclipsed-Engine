#include "Game.h"

#include "Input/InputMapper.h"

#include <Components/Rendering/SpriteRendrer2D.h>
#include <Components/Transform2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Physics/BoxCollider2D.h>
#include <Components/TestingComponents/RotateObjectContin.h>

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "PhysicsEngine.h"

namespace ENGINE_NAMESPACE
{
	void Game::Init()
	{
		Material* matrial = new Material();
		matrial->SetTexture(ASSET_PATH "noah1.png");

		{
			int go = 1;
			SpriteRendrer2D* rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(30.f, 30.f);
			RigidBody2D* rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(15.f, 15.f));
			boxCollider->myLayer = Layer::Player;

			rend->SetMaterial(matrial);
		}

		{
			int go = 2;
			SpriteRendrer2D* rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D* transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -1.f);
			transform->SetScale(1000.f, 10.f);
			BoxCollider2D* boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(500.f, 5.f));
			boxCollider->myLayer = Layer::Ground;

			rend->SetMaterial(matrial);
		}
	}

	void Game::Update()
	{
		float directionMove = InputMapper::ReadValue("Sides");

		if (directionMove)
		{
			RigidBody2D* rb = GetComp(RigidBody2D, 1);

			if (rb)
			{
				float moveSpeed = 1500;
				float velY = rb->GetVelocity().Y;
				rb->SetVelocity({ directionMove * moveSpeed * Time::GetDeltaTime(), velY });
			}
		}

		if (InputMapper::ReadValue("Jump"))
		{
			Transform2D* transform = GetComp(Transform2D, 1);

			HitResults hit;
			if (PhysicsEngine::OverlapSphere(transform->GetPosition() - Math::Vector2f(0.f, 0.07), 0.1f, hit, Layer::Ground))
			{
				RigidBody2D* rb = GetComp(RigidBody2D, 1);
				if (rb)
				{
					float velX = rb->GetVelocity().x;
					rb->SetVelocity({ velX, 4.f });
				}
			}
		}

		// if (InputMapper::ReadValue("Dash"))
		// {
		// 	RigidBody2D *rb = GetComp(RigidBody2D, 1);
		// 	if (rb)
		// 	{
		// 		rb->AddForce({100.f * directionMove, 0});
		// 	}
		// }

		if (Input::GetKeyDown(Keycode::R))
		{
			ComponentManager::RemoveComponent<BoxCollider2D>(1);
		}
		// if (Input::GetKeyDown(Keycode::U))
		// {
		// 	BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(1);
		// 	boxCollider->SetHalfExtents(Math::Vector2f(50.f, 50.f));

		// 	boxCollider->Start();
		// 	boxCollider->Awake();
		// }
	}
}