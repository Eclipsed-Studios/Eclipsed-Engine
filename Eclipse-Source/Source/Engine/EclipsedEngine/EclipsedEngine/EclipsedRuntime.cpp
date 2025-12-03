#include "EclipsedRuntime.h"

#include "CoreEngine/MainSingleton.h"
#include "CoreEngine/Input/Input.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "EntityEngine/ComponentManager.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
//#ifdef ECLIPSED_EDITOR
//#include "CoreEngine/PhysicsDebugDrawer/PhysicsDebugDrawer.h"
//#endif
#include "AssetEngine/AssetPipeline.h"

#include "CoreEngine/PathManager.h"

#include <fstream>


namespace Eclipse
{
	void EclipsedRuntime::StartEngine(const std::string& path)
	{
		PathManager::Init(path);

		Assets::AssetPipeline::Init();

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
		}

		GraphicsEngine::Init();
		engine.Init();


		{ // PHYSICS
			b2DebugDraw debugDraw = { 0 };

			//PhysicsDebugDrawer::Init(&debugDraw);

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

	}

	void EclipsedRuntime::UpdateGame()
	{
		PhysicsEngine::Update();

		ComponentManager::AwakeStartComponents();

		ComponentManager::EarlyUpdateComponents();
		ComponentManager::UpdateComponents();
		ComponentManager::LateUpdateComponents();
	}

	void EclipsedRuntime::Render()
	{
		PhysicsEngine::DrawPhysicsObjects();
		ComponentManager::RenderComponents();
		GraphicsEngine::Render();
	}

	void EclipsedRuntime::Update()
	{
		engine.Update();
		ComponentManager::EditorUpdateComponents();

	}

	void EclipsedRuntime::EndFrame()
	{
		GraphicsEngine::EndFrame();
	}

	bool EclipsedRuntime::BeginFrame()
	{
		GraphicsEngine::BeginFrame();
		int shouldCloseWindow = GraphicsEngine::ShouldWindowClose();

		return !shouldCloseWindow;
	}
}
