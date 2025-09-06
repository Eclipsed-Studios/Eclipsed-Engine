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

#include "Audio/AudioManager.h"

namespace ENGINE_NAMESPACE
{
	void Engine::Init()
	{
		InitSubSystems();

		game.Init();

		ComponentManager::AwakeComponents();
		ComponentManager::StartComponents();
	}

	void Engine::InitSubSystems()
	{
		{ // Sub engines
			GraphicsEngine::Init();

			PhysicsEngine::Init(8, { 0.f, -9.81f });
			PhysicsEngine::myBeginContactCallback = [](UserData& aUserData)
				{
					ComponentManager::BeginCollisions(aUserData.gameobject);
				};
			PhysicsEngine::myEndContactCallback = [](UserData& aUserData)
				{
					ComponentManager::EndCollisions(aUserData.gameobject);
				};
		}

		Time::Init();
		Input::Init();
		ComponentManager::Init();
		AudioManager::Init();

		Utilities::MainSingleton::Init();
	}

	bool Engine::BeginFrame()
	{
		GraphicsEngine::BeginFrame();
		int shouldCloseWindow = GraphicsEngine::ShouldWindowClose();
		return !shouldCloseWindow;
	}
	void Engine::Update()
	{
		AudioManager::Update();

		DebugInformationCollector::ResetRenderCalls();

		PlatformIntegration::IntegrationManager::Update();

		Time::Update();
		Input::Update();

		PhysicsEngine::Update();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();

		game.Update();

		GraphicsEngine::Render();
	}
	void Engine::EndFrame()
	{
		GraphicsEngine::EndFrame();
	}
}