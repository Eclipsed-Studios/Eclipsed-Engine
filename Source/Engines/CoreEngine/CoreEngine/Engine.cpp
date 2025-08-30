#include "Engine.h"

#include <MainSingleton.h>
#include <ECS/ComponentManager.h>
#include <Components/SpriteRendrer2D.h>

#include "ImGui/ImGui/imgui.h"

#include "DebugLogger.h"

namespace ENGINE_NAMESPACE
{
	void Testing_Start()
	{
		ComponentManager::AddComponent<SpriteRendrer2D>(1);
	}

	void Testing_Update()
	{
		
	}

	void Engine::Init()
	{
		Utilities::MainSingleton::Init();

		Testing_Start();

		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
	}

	void Engine::Update()
	{
		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();

		Testing_Update();
	}
}