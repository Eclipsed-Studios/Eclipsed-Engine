#include "EditorRuntime.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "CoreEngine/Engine.h"

#include "CoreEngine/Scenes/SceneManager.h"
#include "CoreEngine/Scenes/SceneLoader.h"

#include "CoreEngine/Input/Input.h"

#include "CoreEngine/Input/InputMapper.h"

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
		DrawPlayGameButtons();
		Engine::Render();
	}
	bool EditorRuntime::BeginFrameEngine()
	{
		return Engine::BeginFrame();
	}
	void EditorRuntime::EndFrameEngine()
	{
		static bool SaveOnce = false;
		if (InputMapper::ReadValue("SaveScene"))
		{
			if (!SaveOnce)
			{
				SaveOnce = true;
				SceneManager::SaveActiveScene();
			}
		}
		else SaveOnce = false;

		Engine::EndFrame();
	}





	void EditorRuntime::DrawPlayGameButtons()
	{
		int windowSizeX = TemporarySettingsSingleton::Get().GetResolutionX() * 0.5f;
		int windowSizeY = TemporarySettingsSingleton::Get().GetResolutionY() * 0.5f;
		Math::Vector2i windowPosition = GraphicsEngine::GetWindowPosition();

		ImGui::Begin("TestGameButons", (bool*)1, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

		if (!isPlaying || isPaused)
		{
			if (ImGui::Button(ICON_FA_PLAY) || Input::GetKeyDown(Keycode::F5))
			{
				isPlaying = true;
				isPaused = false;

				SceneLoader::Save(SceneManager::GetActiveScene());

				ImGui::End();
				return;
			}
		}


		if (isPlaying)
		{
			if (!isPaused)
			{
				if (ImGui::Button(ICON_FA_PAUSE))
					isPaused = !isPaused;
			}

			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_STOP))
			{
				isPlaying = false;
				isPaused = false;

				SceneManager::ReloadActiveScene();
			}
		}

		ImVec2 buttonsWindowSize = ImGui::GetWindowSize();
		ImGui::SetWindowPos(ImVec2(windowPosition.x + windowSizeX - buttonsWindowSize.x * 0.5f, windowPosition.y));

		ImGui::End();
	}
}