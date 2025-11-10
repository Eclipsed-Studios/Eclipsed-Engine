#include "EditorContext.h"

#include "CoreEngine/Engine.h"

#include "CoreEngine/AssetManagement/Resources.h"

#include "AssetEngine/AssetPipeline.h"

#include "AssetEngine/Resources.h"
#include "AssetEngine/Assets/Material.h"

#include <stdlib.h>



#ifdef ECLIPSED_EDITOR
namespace Eclipse::Editor
{
	void EditorContexts::Init(const std::string& projectPath)
	{
		Resources::Init();
		PathManager::Init(projectPath);

		Assets::AssetPipeline::Init();
		Assets::Resourcess::Get<Materials>("Default.mat");

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


		Engine::Init();
		myUIManager.Init();

		myRuntime.Init();
	}

	bool EditorContexts::BeginFrame()
	{
		myUIManager.BeginFrame();
		return myRuntime.BeginFrameEngine();
	}

	void EditorContexts::Update()
	{
		myRuntime.UpdateEngine();

		if (myRuntime.IsPlaying())
		{
			myRuntime.UpdateGame();
		}

		myRuntime.RenderEngine();
		myUIManager.Update();
	}

	void EditorContexts::Render()
	{
		myUIManager.Render();
	}

	void EditorContexts::EndFrame()
	{	
		myRuntime.EndFrameEngine();
	}

	void EditorContexts::Shutdown()
	{

	}
}
#endif