#include "Engine.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#ifdef ECLIPSED_EDITOR
#include "PhysicsDebugDrawer/PhysicsDebugDrawer.h"
#endif

#include "InputEngine/Input.h"
#include "InputEngine/InputMapper.h"

#include "EntityEngine/ComponentManager.h"
#include "Utilities/PlatformIntegration/IntegrationManager.h"

#include <iostream>
#include "Utilities/Reflection/Reflection.h"
#include "Scenes/SceneLoader.h"
#include "Scenes/SceneManager.h"

#include "EntityEngine/Components/AudioSource.h"

#include "EngineSettings.h"

#include "AssetEngine/Resources.h"
#include "AssetEngine/Assets/Texture.h"

namespace Eclipse
{
	void Engine::Init()
	{
		TemporarySettingsSingleton::Get().Init((PathManager::GetEngineLocal() / "EngineSettings.json").generic_string());

		InitSubSystems();

		Utilities::MainSingleton::RegisterInstance<Time>().Init();
		Utilities::MainSingleton::RegisterInstance<Input>().Init();
	}

	void Engine::Internal_Update()
	{
		PhysicsEngine::Update();

		ComponentManager::AwakeStartComponents();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();
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

		ComponentManager::Init();
		//AudioManager::Init();

		SceneManager::LoadSceneData();
	}


	bool Engine::BeginFrame()
	{
		Assets::Resources::Update();
		GraphicsEngine::BeginFrame();
		int shouldCloseWindow = GraphicsEngine::ShouldWindowClose();

		return !shouldCloseWindow;
	}

	void Engine::Update()
	{
		DebugInformationCollector::ResetRenderCalls();

		PlatformIntegration::IntegrationManager::Update();

		Utilities::MainSingleton::GetInstance<Time>().Update();
		Utilities::MainSingleton::GetInstance<Input>().Update();

		ComponentManager::EditorUpdateComponents();
		//AudioManager::Update();
	}

	void Engine::Render()
	{
		PhysicsEngine::DrawPhysicsObjects();
		ComponentManager::RenderComponents();
		GraphicsEngine::Render();
	}

	void Engine::EndFrame()
	{
		GraphicsEngine::EndFrame();
	}
}