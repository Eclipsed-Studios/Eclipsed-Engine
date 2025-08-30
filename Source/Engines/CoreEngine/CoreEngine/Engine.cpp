#include "Engine.h"

#include <ImGui/ImGui/imgui.h>

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include <Components/SpriteRendrer2D.h>
#include <Components/Transform2D.h>
#include <Components/TestingComponents/RotateObjectContin.h>

#include "Timer.h"

#include "DebugLogger.h"

#include "IntegrationManager.h"

namespace ENGINE_NAMESPACE
{
	void Testing_Start()
	{
		auto rend = ComponentManager::AddComponent<SpriteRendrer2D>(1);
		ComponentManager::AddComponent<Transform2D>(1);
		ComponentManager::AddComponent<RotateObjectContin>(1);

		Material* matrial = new Material();
		matrial->SetTexture(ASSET_PATH"noah1.png");
		rend->SetMaterial(matrial);
		ComponentManager::AddComponent<Transform2D>(2);
	}

	void Testing_Update()
	{
		
	}

	void Engine::Init()
	{
		Time::Init();

		Utilities::MainSingleton::Init();

		Testing_Start();

		auto rend = ComponentManager::GetComponent<SpriteRendrer2D>(2);

		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
	}

	void Engine::Update()
	{
		PlatformIntegration::IntegrationManager::Update();
		Time::Update();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();

		Testing_Update();
	}
}