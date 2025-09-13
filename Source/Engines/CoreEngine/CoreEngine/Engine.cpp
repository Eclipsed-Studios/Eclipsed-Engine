#include "Engine.h"

#include "PhysicsEngine.h"
#include "OpenGL/OpenGLGraphicsAPI.h"

#include "OpenGL/DebugDrawers/PhysicsDebugDrawer.h"

#include "Timer.h"
#include "Input/Input.h"
#include "Input/InputMapper.h"

#include "MainSingleton.h"
#include "Debug/DebugInformationCollector.h"

#include "ECS/ComponentManager.h"
#include "PlatformIntegration/IntegrationManager.h"
#include "SettingsManager.h"
#include "Audio/AudioManager.h"

#include <iostream>
#include "Reflection/Reflection.h"

namespace Eclipse
{
	void Engine::Init()
	{
		TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);

		InitSubSystems();

		game.Init();
	}

	void Engine::InitSubSystems()
	{
		GraphicsEngine::Init();

		{ // PHYSICS
			b2DebugDraw debugDraw = { 0 };

			PhysicsDebugDrawer::Init(&debugDraw);

			PhysicsEngine::Init(8, { 0.f, -9.81f }, debugDraw);
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

		ComponentManager::AwakeStartComponents();

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