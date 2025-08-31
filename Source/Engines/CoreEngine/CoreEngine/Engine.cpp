#include "Engine.h"

#include <ImGui/ImGui/imgui.h>

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include <Components/SpriteRendrer2D.h>
#include <Components/Transform2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Physics/BoxCollider2D.h>
#include <Components/TestingComponents/RotateObjectContin.h>

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "DebugLogger.h"
#include "IntegrationManager.h"

#include "PhysicsEngine.h"

#include "box2d/box2d.h"

namespace ENGINE_NAMESPACE
{
	void Testing_Start()
	{
		Material *matrial = new Material();
		matrial->SetTexture(ASSET_PATH "noah1.png");

		{
			int go = 1;
			SpriteRendrer2D *rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D *transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetScale(100.f, 100.f);
			RigidBody2D *rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(50.f, 50.f));
			rend->SetMaterial(matrial);
		}

		{
			int go = 2;
			SpriteRendrer2D *rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D *transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -700.f * 0.25f);
			transform->SetScale(1000.f, 20.f);
			BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(500.f, 10.f));
			rend->SetMaterial(matrial);
		}
	}

	void Testing_Update()
	{
		float directionMove = Input::GetKey(keycode::D) - Input::GetKey(keycode::A);

		if (directionMove)
		{
			RigidBody2D *rb = GetComp(RigidBody2D, 1);

			if (rb)
			{
				float moveSpeed = 40000;
				float velY = rb->GetVelocity().Y;
				rb->SetVelocity({directionMove * moveSpeed * Time::GetDeltaTime(), velY});
			}
		}

		if (Input::GetKeyDown(keycode::SPACE))
		{
			RigidBody2D *rb = GetComp(RigidBody2D, 1);
			if (rb)
				rb->AddForce({0, 300.f});
		}

		if (Input::GetKeyDown(keycode::R))
		{
			ComponentManager::RemoveComponent<BoxCollider2D>(1);
		}
		if (Input::GetKeyDown(keycode::U))
		{
			BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(1);
			boxCollider->SetHalfExtents(Math::Vector2f(50.f, 50.f));

			boxCollider->Start();
			boxCollider->Awake();
		}
	}

	void Engine::Init()
	{
		Time::Init();
		Input::Init();

		Utilities::MainSingleton::Init();

		PhysicsEngine::Init();
		
		Testing_Start();
		
		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
		
	}

	void Engine::Update()
	{
		PlatformIntegration::IntegrationManager::Update();

		Time::Update();
		Input::Update();

		PhysicsEngine::Update();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();

		Testing_Update();
	}
}