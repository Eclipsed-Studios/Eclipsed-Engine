#include "Engine.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include "Timer.h"
#include "Input/Input.h"

#include "IntegrationManager.h"

#include "PhysicsEngine.h"

#include "Input/InputMapper.h"

#include <iostream>

namespace ENGINE_NAMESPACE
{
	void Engine::Init()
	{
		GraphicsEngine::Get().Init();

		Time::Init();
		Input::Init();
		ComponentManager::Init();

		Utilities::MainSingleton::Init();
		PhysicsEngine::Init();

		game.Init();

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

		game.Update();

		GraphicsEngine::Get().Render();
	}
	void Engine::End()
	{
		GraphicsEngine::Get().End();
	}
}