#include "Engine.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include <ImGui/ImGui/imgui.h>

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include <Components/Rendering/SpriteRendrer2D.h>
#include <Components/Transform2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Physics/BoxCollider2D.h>
#include <Components/TestingComponents/RotateObjectContin.h>

#include "Timer.h"
#include "Input/Input.h"
#include "Input/Keycodes.h"

#include "IntegrationManager.h"

#include "PhysicsEngine.h"

#include "Input/InputMapper.h"

//#include "DebugLogger.h"

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
			transform->SetScale(30.f, 30.f);
			RigidBody2D *rb = ComponentManager::AddComponent<RigidBody2D>(go);
			rb->SetRotationLocked(true);

			BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(15.f, 15.f));
			rend->SetMaterial(matrial);
		}

		{
			int go = 2;
			SpriteRendrer2D *rend = ComponentManager::AddComponent<SpriteRendrer2D>(go);
			Transform2D *transform = ComponentManager::AddComponent<Transform2D>(go);
			transform->SetPosition(0, -1.f);
			transform->SetScale(1000.f, 10.f);
			BoxCollider2D *boxCollider = ComponentManager::AddComponent<BoxCollider2D>(go);
			boxCollider->SetHalfExtents(Math::Vector2f(500.f, 5.f));
			rend->SetMaterial(matrial);
		}
	}

	void Testing_Update()
	{
		float directionMove = InputMapper::ReadValue("Sides");

		if (directionMove)
		{
			RigidBody2D *rb = GetComp(RigidBody2D, 1);

			if (rb)
			{
				float moveSpeed = 150;
				float velY = rb->GetVelocity().Y;
				rb->SetVelocity({directionMove * moveSpeed * Time::GetDeltaTime(), velY});
			}
		}

		if (InputMapper::ReadValue("Jump"))
		{
			RigidBody2D *rb = GetComp(RigidBody2D, 1);
			if (rb)
			{
				float velX = rb->GetVelocity().x;
				rb->SetVelocity({velX, 4.f});
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

	void Engine::Init()
	{
		GraphicsEngine::Get().Init();

		Time::Init();
		Input::Init();
		ComponentManager::Init();

		Utilities::MainSingleton::Init();
		PhysicsEngine::Init();

		Testing_Start();

		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
	}

	bool Engine::Begin()
	{
		GraphicsEngine::Get().Begin();
		int shouldCloseWindow = GraphicsEngine::Get().ShouldWindowClose();
		return !shouldCloseWindow;
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

		GraphicsEngine::Get().Render();

		Testing_Update();
	}
	void Engine::End()
	{
		GraphicsEngine::Get().End();
	}
}