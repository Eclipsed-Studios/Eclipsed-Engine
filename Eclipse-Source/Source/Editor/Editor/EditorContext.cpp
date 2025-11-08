#include "EditorContext.h"

#include "CoreEngine/Engine.h"

#include "CoreEngine/AssetManagement/Resources.h"

#include "AssetEngine/AssetPipeline.h"

#include "AssetEngine/Resources.h"
#include "AssetEngine/Assets/Material.h"




#ifdef ECLIPSED_EDITOR
namespace Eclipse::Editor
{
	void EditorContexts::Init(const std::string& projectPath)
	{
		//DebugLogger::OverwriteDefaultCoutBuffer();

		Resources::Init();
		PathManager::Init(projectPath);

		Assets::AssetPipeline::Init();
		Assets::Resourcess::Get<Materials>("Default.mat");


		Engine::Init();
		myUIManager.Init();
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