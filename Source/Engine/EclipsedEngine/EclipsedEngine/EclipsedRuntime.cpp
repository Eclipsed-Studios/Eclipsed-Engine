#include "EclipsedRuntime.h"

#include "CoreEngine/MainSingleton.h"
#include "CoreEngine/Input/Input.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "EntityEngine/ComponentManager.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#include "AssetEngine/AssetManager.h"
#include "CoreEngine/PlatformIntegration/IntegrationManager.h"

#include "CoreEngine/PathManager.h"

#include "Scenes/SceneManager.h"
#include "AudioEngine/AudioManager.h"

#include <fstream>

#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "Replication/ReplicationManager.h"

#include "Steam/SteamGeneral.h"

#include "CoreEngine/Settings/GraphicsSettings.h"

#include "EclipsedEngine/Editor/PhysicsDebugDrawer.h"

#include "EclipsedEngine/Components/ComponentForcelink.h"

#include "AssetEngine/Helper/TextManager.h"
#include "Networking.h"


#ifdef ECLIPSED_NETWORKING
#include "NetworkEngine/Client/SteamP2PNetworkingClient.h"
#include "NetworkEngine/Server/SteamP2PNetworkingServer.h"
#endif

#include "CoreEngine/Profiling/PerformanceProfilerManager.h"

#ifdef ECLIPSED_EDITOR
#include "ECS/ObjectManager.h"
#include "Editor/Windows/WindowTypes/AssetWindow/AssetWindow.h"
#endif

#include "CoreEngine/Settings/ConfigManager.h"

namespace Eclipse
{
	EclipsedRuntime* EclipsedRuntime::runtime{};

	EclipsedRuntime& EclipsedRuntime::Get()
	{
		return *runtime;
	}

	EclipsedRuntime::EclipsedRuntime()
	{
		runtime = this;
	}


#ifdef ECLIPSED_EDITOR
	void EclipsedRuntime::StartEngine(const std::string& path)
#else
	void EclipsedRuntime::StartEngine()
#endif
	{
		time.Init();

		componentManager.SetIntance(componentManager);

#ifndef ECLIPSED_EDITOR
		SteamGeneral::Get().Init();

		//renderThread = std::thread();
		Assets::AssetManager::ImportBundle();
#endif
#ifdef ECLIPSED_NETWORKING
		Replication::ReplicationManager::Init();
#endif // 

		//Configs::ConfigManager::Init();

		AudioManager::Init();

		ComponentForcelink::LinkComponents();
		//Resources::Init();

#ifdef ECLIPSED_EDITOR
		{
			const char* appData = std::getenv("APPDATA");

			std::filesystem::path path = appData;
			path /= "EclipsedEngine";

			if (!std::filesystem::exists(path))
			{
				std::filesystem::create_directories(path);
			}

			path /= "EnginePath.txt";

			std::ofstream out(path);

			std::string engineRoot = PathManager::GetEngineRoot().generic_string();
			out.write(engineRoot.c_str(), engineRoot.size());
			out.close();

			Editor::AssetWindow::CreateGameobjectFunc = [](char* data) { return InternalSpawnObjectClass::CreateObjectFromJsonString(data)->GetID(); };
			Editor::AssetWindow::InitNewPhysicsScene = [this]() { physicsEngine.InitWorld(); };
		}

#endif



		//MainSingleton::RegisterInstance<EngineSettings>();
		MainSingleton::RegisterInstance<TextManager>();

		GraphicsEngine::InitSpecifiedAPI<OpenGLGraphicsEngine>();
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->Init();
		input.Init();

		//Settings::SettingsRegistry::SaveDefaults();

		{
			// PHYSICS
			b2DebugDraw debugDraw = { 0 };

			PhysicsDebugDrawer::Init(&debugDraw);

			physicsEngine.Init(physicsEngine, 8, { 0.f, -9.82f }, debugDraw);
			physicsEngine.myBeginContactCallback = [this](UserData& aUserData)
				{
					componentManager.BeginCollisions(aUserData.gameobject);
				};
			physicsEngine.myEndContactCallback = [this](UserData& aUserData)
				{
					componentManager.EndCollisions(aUserData.gameobject);
				};
		}

		EventSystem::Trigger("Engine-Load");
	}

	void EclipsedRuntime::LateStart()
	{
		SceneManager::Initialize();

		SceneManager::LoadSceneData();

#ifndef ECLIPSED_EDITOR
		SceneManager::LoadScene("NewScene");
#endif
	}

	void EclipsedRuntime::UpdateGame()
	{
		CORE_PROFILE_SCOPED;
		//TODO: Might not want to call every frame but it does now
		SteamGeneral::Get().Update();

		physicsEngine.Update();

		componentManager.AwakeStartComponents();

		componentManager.EarlyUpdateComponents();
		componentManager.UpdateComponents();

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

#ifdef ECLIPSED_EDITOR
		physicsEngine.DrawPhysicsObjects();
#endif
		componentManager.RenderComponents();
		componentManager.EditorLateUpdateComponents();
		componentManager.LateUpdateComponents();
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->Render();
	}

	void EclipsedRuntime::Update()
	{
		CORE_PROFILE_SCOPED;
		time.Update();
		input.Update();

		PlatformIntegration::IntegrationManager::Update();

#ifndef ECLIPSED_EDITOR
		Math::Vector2f mousePos = input.GetMousePos();

		const Math::Vector2i& resolution = Settings::GraphicsSettings::GetResolution();

		float mousePosNormalizedX = mousePos.x / resolution.x;
		float mousePosNormalizedY = mousePos.y / resolution.y;

		input.SetGamePosition({ mousePosNormalizedX, 1 - mousePosNormalizedY });
#endif

		componentManager.EditorUpdateComponents();
	}

	void EclipsedRuntime::EndFrame()
	{
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->EndFrame();
		Assets::AssetManager::EndFrame();
		PerformanceProfilerManager::Clear();
	}

	void EclipsedRuntime::Shutdown()
	{
		EventSystem::Trigger("Engine-Shutdown");
		MainSingleton::Destroy();

		SHUT_DOWN_NETWORK_ENGINE();
	}

	bool EclipsedRuntime::BeginFrame()
	{
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->BeginFrame();
		int shouldCloseWindow = GraphicsEngine::Get<OpenGLGraphicsEngine>()->ShouldWindowClose();

		return !shouldCloseWindow;
	}

	Input& EclipsedRuntime::GetInput()
	{
		return input;
	}

	Time& EclipsedRuntime::GetTime()
	{
		return time;
	}

	ClassRegistry& EclipsedRuntime::GetClassReg()
	{
		return clsReg;
	}
}
