#include "Engine.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include <ECS/ComponentManager.h>
#include <MainSingleton.h>

#include "Timer.h"
#include "Input/Input.h"

#include "PlatformIntegration/IntegrationManager.h"

#include "PhysicsEngine.h"

#include "Input/InputMapper.h"

#include <iostream>

#include "Debug/DebugInformationCollector.h"

#include "SettingsManager.h"

namespace ENGINE_NAMESPACE
{
	void Engine::Init()
	{
		SettingsManager::Load();

		GraphicsEngine::Get().Init();

		Time::Init();
		Input::Init();
		ComponentManager::Init();

		Utilities::MainSingleton::Init();
		PhysicsEngine::Init(8, { 0.f, -9.81f });

		PhysicsEngine::myBeginContactCallback = [](UserData& aUserData)
			{
				ComponentManager::BeginCollisions(aUserData.gameobject);
			};
		PhysicsEngine::myEndContactCallback = [](UserData& aUserData)
			{
				ComponentManager::BeginCollisions(aUserData.gameobject);
			};

		game.Init();

		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
	}

	bool Engine::BeginFrame()
	{
		GraphicsEngine::Get().BeginFrame();
		int shouldCloseWindow = GraphicsEngine::Get().ShouldWindowClose();
		return !shouldCloseWindow;
	}
	void Engine::Update()
	{
		DebugInformationCollector::ResetRenderCalls();

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
	void Engine::EndFrame()
	{
		GraphicsEngine::Get().EndFrame();
	}
}