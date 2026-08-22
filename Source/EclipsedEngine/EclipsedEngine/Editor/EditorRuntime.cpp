#ifdef ECL_EDITOR
#include "EditorRuntime.h"

#include "Renderer/OpenGL/OpenGLGraphicsAPI.h"

#include "EclipsedEngine/Scenes/SceneManager.h"
#include "EclipsedEngine/Scenes/SceneLoader.h"

#include "Input/Input.h"

#include "Game/GameLoader.h"

#include "Core/Files/FileWatcher.h"

#include "Core/PathManager.h"

#include "FontAwesome/7/IconsFontAwesome7.h"
#include "Core/Settings/GraphicsSettings.h"
#include "Core/Settings/EditorSettings.h"

#include "Assets/AssetManager.h"
//#include "Assets/AssetDatabase.h"

#include <ImGui/imgui.h>

#include "EclipsedEngine/Components/ComponentForcelink.h"
#include "ECS/ComponentManager.h"

#include "EclipsedEngine/Steam/SteamGeneral.h"

#include "EclipsedEngine/Editor/Windows/WindowTypes/HierarchyWindow.h"

#include "EclipsedEngine/ECS/ObjectManager.h"

#include "Physics/PhysicsEngine.h"

#include "Assets/AssetImporter.h"

namespace Eclipse::Editor
{
	void EditorRuntime::Init(const std::string& path)
	{
		EditorEntry& editorEntry = MainSingleton::RegisterInstance<EditorEntry>();
		editorEntry.IsPlaying = &isPlaying;
		editorEntry.IsPaused = &isPaused;


		PathManager::Init(path);

		eclipseRuntime.StartEngine(path);


		{ 
			//Assets::AssetImporter::ImportAssets(PathManager::GetEngineAssetsPath(), "Engine/");
			Assets::AssetImporter::ImportAssets(PathManager::GetAssetsPath(), "Assets/");
		}
		eclipseRuntime.LateStart();



		if (std::filesystem::exists(PathManager::GetGameDllBuildPath() / "Game.dll")) GameLoader::LoadGameDLL();

		try
		{
			SceneManager::LoadScene(Settings::EditorSettings::GetLastActiveScene());
		}
		catch (std::exception e)
		{
			// The scene has been removed.
		}

		//ComponentManager::Get().Init();
	}

	void EditorRuntime::SetGameChanged(const FileWatcherEvent& e)
	{
		std::string ext = std::filesystem::path(e.path).extension().string();

		if (ext == ".h" || ext == ".cpp" || ext == ".hpp" || ext == ".inl" || ext == ".c")
		{
			gameChanged = true;
		}
	}

	void EditorRuntime::LoadDLL()
	{

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
	{}

	void EditorRuntime::PauseGame()
	{}

	void EditorRuntime::UnpauseGame()
	{}

	bool EditorRuntime::IsPlaying()
	{
		return isPlaying && !isPaused;
	}
	void EditorRuntime::UpdateEngine()
	{
		// GLFWwindow* window = MainSingleton::GetInstance<GLFWwindow*>();
		// if (glfwGetWindowAttrib(window, GLFW_FOCUSED) && gameChanged)
		// {
		// 	LoadDLL();
		// }

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
		const Math::Vector2i& resolution = Settings::GraphicsSettings::GetResolution();


		int windowSizeX = resolution.x * 0.5f;
		int windowSizeY = resolution.y * 0.5f;
		Math::Vector2i windowPosition = GraphicsEngine::Get()->GetWindowPosition();

		ImGui::Begin("TestGameButons", (bool*)1, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize );

		if (!isPlaying || isPaused)
		{
			if (ImGui::Button(ICON_FA_PLAY) || Input::GetKeyDown(Keycode::F5))
			{
				isPlaying = true;
				isPaused = false;

				SteamGeneral::Get().Init();

				if (SceneManager::GetActiveSceneType() == SceneManager::Default)
					SceneManager::SaveActiveScene();
				else if (SceneManager::GetActiveSceneType() == SceneManager::Prefab)
				{
					std::filesystem::path filePath = SceneManager::GetActiveScene();
					filePath.replace_filename("");
					HierarchyWindow::CreatePrefab(SceneManager::ActivePrefabEditSceneID, filePath);
				}

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

#ifdef ECLIPSED_NETWORKING
				Replication::ReplicationManager::CloseConnection("Disconnect : Quit Game");
#endif

				SteamGeneral::Get().ShutDown();

				if (SceneManager::GetActiveSceneType() == SceneManager::Default)
					SceneManager::ReloadActiveScene();
				else if (SceneManager::GetActiveSceneType() == SceneManager::Prefab)
				{
					std::filesystem::path filePath = SceneManager::GetActiveScene();

					{
						std::ifstream stream(filePath);
						if (!stream.is_open())
							return;

						SceneManager::UnloadScene();
						PhysicsEngine::InitWorld();

						SceneManager::SetActiveSceneType(SceneManager::Prefab);
						SceneManager::SetActiveScene(filePath.generic_string().c_str());


						size_t prefSize = std::filesystem::file_size(filePath);
						char* data = reinterpret_cast<char*>(malloc(prefSize + 1));
						stream.read(data, prefSize);
						memset(data + prefSize, '\0', 1);
						stream.close();

						GameObject* gameobject = InternalSpawnObjectClass::CreateObjectFromJsonString(data);
						SceneManager::ActivePrefabEditSceneID = gameobject->GetID();

						free(data);
					}
				}
			}
		}

		ImVec2 buttonsWindowSize = ImGui::GetWindowSize();
		ImGui::SetWindowPos(ImVec2(windowPosition.x + windowSizeX - buttonsWindowSize.x * 0.5f, windowPosition.y));

		ImGui::End();
	}
}
#endif