#include "EditorRuntime.h"

#include "CoreEngine/Engine.h"

namespace Eclipse::Editor
{
	void EditorRuntime::UpdateGame()
	{
		Engine::Internal_Update();
	}

	void EditorRuntime::EnterPlayMode()
	{
		Engine::Render();
	}

	void EditorRuntime::ExitPlayMode()
	{
	}

	void EditorRuntime::PauseGame()
	{
	}

	void EditorRuntime::UnpauseGame()
	{
	}

	bool EditorRuntime::IsPlaying()
	{
		return isPlaying && !isPaused;
	}
	void EditorRuntime::UpdateEngine()
	{
		Engine::Update();
	}
	void EditorRuntime::RenderEngine()
	{
		Engine::Render();
	}
	bool EditorRuntime::BeginFrameEngine()
	{
		return Engine::BeginFrame();
	}
	void EditorRuntime::EndFrameEngine()
	{
		Engine::EndFrame();
	}
}