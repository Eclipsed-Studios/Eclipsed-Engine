#include "pch.h"

#include "Engine.h"

#include "PlatformIntegration/IntegrationManager.h"

namespace Eclipse
{
	void Engine::Init()
	{
		Time::Init();
		Input::Init();
	}

	void Engine::Update()
	{
		PlatformIntegration::IntegrationManager::Update();

		Time::Init();
		Input::Update();
	}
}