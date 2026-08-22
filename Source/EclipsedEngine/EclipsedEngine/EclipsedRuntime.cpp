#include "EclipsedRuntime.h"

#include "Core/MainSingleton.h"
#include "Input/Input.h"

#include "Physics/PhysicsEngine.h"
#include "ECS/ComponentManager.h"
#include "Renderer/OpenGL/OpenGLGraphicsAPI.h"

#include "Assets/AssetManager.h"

#include "Core/PathManager.h"

#include "Scenes/SceneManager.h"
#include "Audio/AudioManager.h"

#include <fstream>

#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "Replication/ReplicationManager.h"

#include "Steam/SteamGeneral.h"

#include "Core/Settings/GraphicsSettings.h"

#include "EclipsedEngine/Editor/PhysicsDebugDrawer.h"

#include "EclipsedEngine/Components/ComponentForcelink.h"

#include "Networking.h"


#ifdef ECLIPSED_NETWORKING
	#include "Networking/Client/SteamP2PNetworkingClient.h"
	#include "Networking/Server/SteamP2PNetworkingServer.h"
#endif

#include "Core/Profiling/PerformanceProfilerManager.h"

#ifdef ECL_EDITOR
	#include "ECS/ObjectManager.h"
	#include "Editor/Windows/WindowTypes/AssetWindow/AssetWindow.h"
#endif

#include "Core/Settings/ConfigManager.h"

#include "ECS/ComponentManager.h"
#include "Physics/PhysicsEngine.h"

#include "Assets/AssetImporter.h"

namespace Eclipse
{
#ifdef ECL_EDITOR
	void EclipsedRuntime::StartEngine(const std::string& path)
#else
	void EclipsedRuntime::StartEngine()
#endif
	{
		Core::Timer::Init();

#ifndef ECL_EDITOR
	#ifdef STEAMSDK_PRESENT
		SteamGeneral::Get().Init();
	#endif // STEAMSDK_PRESENT


		//renderThread = std::thread();
		Assets::AssetImporter::ImportBundle();
#endif

#ifdef ECLIPSED_NETWORKING
		Replication::ReplicationManager::Init();
#endif // ECLIPSED_NETWORKING

		AudioManager::Init();


#ifdef ECL_EDITOR
		Editor::AssetWindow::CreateGameobjectFunc = [](char* data) { return InternalSpawnObjectClass::CreateObjectFromJsonString(data)->GetID(); };
		Editor::AssetWindow::InitNewPhysicsScene = [this]() { PhysicsEngine::InitWorld(); };
#endif

		engine.Init();


		//MainSingleton::RegisterInstance<EngineSettings>();
		//MainSingleton::RegisterInstance<TextManager>();

		GraphicsEngine::InitSpecifiedAPI<OpenGLGraphicsEngine>();
		GraphicsEngine::Get()->Init();

		Input& input = MainSingleton::RegisterInstance<Input>();
		input.Init();

		{
			// PHYSICS
			b2DebugDraw debugDraw = { 0 };

			PhysicsDebugDrawer::Init(&debugDraw);

			PhysicsEngine::Init(8, { 0.f, -9.82f }, debugDraw);
			PhysicsEngine::myBeginContactCallback = [this](UserData& aUserData)
				{
					ComponentManager::BeginCollisions(aUserData.gameobject);
				};
			PhysicsEngine::myEndContactCallback = [this](UserData& aUserData)
				{
					ComponentManager::EndCollisions(aUserData.gameobject);
				};
		}


	}

	void EclipsedRuntime::LateStart()
	{
		SceneManager::Initialize();

		SceneManager::LoadSceneData();

#ifndef ECL_EDITOR
		SceneManager::LoadScene("NewScene");
#endif
	}

	void EclipsedRuntime::UpdateGame()
	{
		CORE_PROFILE_SCOPED;
		//TODO: Might not want to call every frame but it does now
		SteamGeneral::Get().Update();

		PhysicsEngine::Update();

		ComponentManager::AwakeStartComponents();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();

		AudioManager::Update();

#ifdef ECLIPSED_NETWORKING
		Replication::ReplicationManager::Update();
#endif
	}

	void SortComponents()
	{
		// const std::vector<Component*>& AllComponents = ComponentManager::GetAllComponents();
		//
		// std::vector<int> ComponentsIndecies;
		// ComponentManager::GetAllComponentsOfTypePtr<BaseUI>(ComponentsIndecies);
		//
		// std::vector<BaseUI*> UiComponents;
		// for (auto& component : ComponentsIndecies)
		// 	UiComponents.emplace_back(reinterpret_cast<BaseUI*>(AllComponents[component]));
		//       
		// std::sort(UiComponentsIndecies.begin(), UiComponentsIndecies.end(), [](BaseUI* aBaseUI0, BaseUI* aBaseUI1)
		// {
		// 	return aBaseUI0->GetZIndex() < aBaseUI1->GetZIndex();
		// });
	}

	void EclipsedRuntime::Render()
	{
		CORE_PROFILE_SCOPED;
		SortComponents();

#ifdef ECL_EDITOR
		//PhysicsEngine::DrawPhysicsObjects();
#endif
		ComponentManager::RenderComponents();
		ComponentManager::EditorLateUpdateComponents();
		ComponentManager::LateUpdateComponents();
		GraphicsEngine::Get()->Render();
	}

	void EclipsedRuntime::Update()
	{
		CORE_PROFILE_SCOPED;
		engine.Update();
		Input::Update();


#ifndef ECL_EDITOR
		Math::Vector2f mousePos = Input::GetMousePos();

		const Math::Vector2i& resolution = Settings::GraphicsSettings::GetResolution();

		float mousePosNormalizedX = mousePos.x / resolution.x;
		float mousePosNormalizedY = mousePos.y / resolution.y;

		Input::SetGamePosition({ mousePosNormalizedX, 1 - mousePosNormalizedY });
#endif

		ComponentManager::EditorUpdateComponents();
	}

	void EclipsedRuntime::EndFrame()
	{
		GraphicsEngine::Get()->EndFrame();
		Assets::AssetManager::EndFrame();
		PerformanceProfilerManager::Clear();
	}

	void EclipsedRuntime::Shutdown()
	{
		MainSingleton::Destroy();
		engine.End();

		SHUT_DOWN_NETWORK_ENGINE();
	}

	bool EclipsedRuntime::BeginFrame()
	{
		GraphicsEngine::Get()->BeginFrame();
		int shouldCloseWindow = GraphicsEngine::Get()->ShouldWindowClose();

		return !shouldCloseWindow;
	}
}
