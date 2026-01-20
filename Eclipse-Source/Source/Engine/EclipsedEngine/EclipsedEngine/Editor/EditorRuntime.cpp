#include "EditorRuntime.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "CoreEngine/Engine.h"

#include "EclipsedEngine/Scenes/SceneManager.h"
#include "EclipsedEngine/Scenes/SceneLoader.h"

#include "CoreEngine/Input/Input.h"

#include "CoreEngine/Input/InputMapper.h"
#include "Game/GameCompiler.h"
#include "Game/GameLoader.h"

#include "CoreEngine/Files/FileWatcher.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include "EclipsedEngine/Components/ComponentForcelink.h"
#include "AssetEngine/AssetPipeline.h"
#include "CoreEngine/PathManager.h"
#include "CoreEngine/MainSingleton.h"
#include "CoreEngine/Settings/EngineSettings.h"

#include "Font-Awesome/7/IconsFontAwesome7.h"
#include "CoreEngine/Settings/GraphicsSettings.h"


namespace Eclipse::Editor
{
	void EditorRuntime::Init(const std::string& path)
	{
		PathManager::Init(path);


		ComponentForcelink::LinkComponents();
		eclipseRuntime.StartEngine(path);


		FileWatcher::Subscribe((PathManager::GetProjectRoot() / "Source").generic_string(), [this](const FileWatcherEvent& e) {SetGameChanged(e);});


		// TODO: Transfer into Replication.h or ReplicationManager.h
		{
			ComponentManager::SetCreateComponentReplicated([](Component* aComponent)
				{
					if (!MainSingleton::Exists<Client>())
						return;

					NetMessage message;
					Replication::ReplicationManager::CreateComponentMessage(aComponent, message);
					MainSingleton::GetInstance<Client>().Send(message);
				});

			ComponentManager::SetDestroyGameObjectReplicated([](unsigned aGameObject)
				{
					if (!MainSingleton::Exists<Client>())
						return;

					NetMessage message;
					Replication::ReplicationManager::DeleteGOMessage(aGameObject, message);
					MainSingleton::GetInstance<Client>().Send(message);
				});

			ComponentManager::SetDeleteReplicationComponent([](unsigned aComponentID) { Replication::ReplicationManager::DeleteReplicatedComponent(aComponentID); });
			ComponentManager::SetBeforeAfterComponentConstruction(
				[]() { Replication::ReplicationManager::SetBeforeReplicatedList(); },
				[]() { Replication::ReplicationManager::SetAfterReplicatedList(); });
		}

		LoadDLL();
	}

	void EditorRuntime::SetGameChanged(const FileWatcherEvent&)
	{
		gameChanged = true;
	}

	void EditorRuntime::LoadDLL()
	{
		std::string sceneName = SceneManager::GetActiveScene();
		ComponentManager::Clear();

		GameLoader::UnloadGameDLL();

		std::filesystem::remove(PathManager::GetProjectRoot() / "Cache/Debug/Game.dll");
		std::filesystem::remove(PathManager::GetProjectRoot() / "Cache/Debug/Game.pdb");

		GameCompiler::CompileGame();
		GameLoader::LoadGameDLL();

		gameChanged = false;

		SceneManager::LoadScene(sceneName);
	}

	void EditorRuntime::UpdateGame()
	{
		eclipseRuntime.UpdateGame();
	}

	void EditorRuntime::EnterPlayMode()
	{
		eclipseRuntime.Render();
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
		GLFWwindow* window = MainSingleton::GetInstance<GLFWwindow*>();
		if (glfwGetWindowAttrib(window, GLFW_FOCUSED) && gameChanged)
		{
			LoadDLL();
		}

		eclipseRuntime.Update();
	}
	void EditorRuntime::RenderEngine()
	{
		DrawPlayGameButtons();
		eclipseRuntime.Render();
	}
	bool EditorRuntime::BeginFrameEngine()
	{
		return eclipseRuntime.BeginFrame();
	}
	void EditorRuntime::EndFrameEngine()
	{
		// static bool SaveOnce = false;
		// if (InputMapper::ReadValue("SaveScene"))
		// {
		// 	if (!SaveOnce)
		// 	{
		// 		SaveOnce = true;
		// 		SceneManager::SaveActiveScene();
		// 	}
		// }
		// else SaveOnce = false;

		eclipseRuntime.EndFrame();

		ComponentManager::CommitDestroy();
	}





	void EditorRuntime::Shutdown()
	{
		eclipseRuntime.Shutdown();
	}

	void EditorRuntime::DrawPlayGameButtons()
	{
		const Math::Vector2i& resolution = Settings::GraphicsSettings::GetData().Resolution;


		int windowSizeX = resolution.x * 0.5f;
		int windowSizeY = resolution.y * 0.5f;
		Math::Vector2i windowPosition = GraphicsEngine::GetWindowPosition();

		ImGui::Begin("TestGameButons", (bool*)1, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

		if (!isPlaying || isPaused)
		{
			if (ImGui::Button(ICON_FA_PLAY) || Input::GetKeyDown(Keycode::F5))
			{
				isPlaying = true;
				isPaused = false;

				SceneLoader::Save(SceneManager::GetActiveScene());

				Replication::ReplicationManager::Start();

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