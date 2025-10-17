#include "Engine.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#ifdef ECLIPSED_EDITOR
#include "PhysicsDebugDrawer/PhysicsDebugDrawer.h"
#endif

#include "Input/Input.h"
#include "Input/InputMapper.h"

#include "ECS/ComponentManager.h"
#include "Utilities/PlatformIntegration/IntegrationManager.h"
#include "Audio/AudioManager.h"

#include <iostream>
#include "Utilities/Reflection/Reflection.h"
#include "Scenes/SceneLoader.h"
#include "Scenes/SceneManager.h"

#include "Components/AudioSource.h"

#include "EngineSettings.h"

namespace Eclipse
{
	void Engine::Init()
	{

		TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);

		InitSubSystems();

		//Game::Init();
	}

	void Engine::Internal_Update()
	{
		//static 
	}

	void Engine::InitSubSystems()
	{
		Resources::Init();

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
		//AudioManager::Init();

		SceneManager::LoadSceneData();

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
		DebugInformationCollector::ResetRenderCalls();

		PlatformIntegration::IntegrationManager::Update();

		Time::Update();
		Input::Update();

		ComponentManager::EditorUpdateComponents();

#ifndef _GAME
		//if (Game::IsPlaying && !Game::IsPaused)
		{
#endif
			//AudioManager::Update();
			PhysicsEngine::Update();

			ComponentManager::AwakeStartComponents();

			ComponentManager::EarlyUpdateComponents();
			ComponentManager::UpdateComponents();
			ComponentManager::LateUpdateComponents();
#ifndef _GAME
		}
#endif

		PhysicsEngine::DrawPhysicsObjects();
		ComponentManager::RenderComponents();
		GraphicsEngine::Render();
	}
	void Engine::EndFrame()
	{
		GraphicsEngine::EndFrame();
	}
}