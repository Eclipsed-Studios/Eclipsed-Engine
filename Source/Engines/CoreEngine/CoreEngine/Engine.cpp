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
		ComponentManager::AddComponent<SpriteRendrer2D>(1);
		ComponentManager::AddComponent<Transform2D>(1);
		ComponentManager::AddComponent<RotateObjectContin>(1);

		ComponentManager::AddComponent<SpriteRendrer2D>(2);
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