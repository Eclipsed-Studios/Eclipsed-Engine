#ifdef ECLIPSED_EDITOR
#include "Editor.h"

#include "CoreEngine/Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "Utilities/PlatformIntegration/DiscordIntegration.h"

#include "CoreEngine/AssetManagement/MetaFileRegistry.h"

#include "Utilities/Math/Math.h"

#include <fstream>
#include <rapidjson/rapidjson/stringbuffer.h>
#include <rapidjson/rapidjson/prettywriter.h>

#include "CoreEngine/Scenes/SceneLoader.h"

#include "Font-Awesome/7/IconsFontAwesome7.h"

#include "CoreEngine/AssetManagement/MetaFileRegistry.h"
#include "CoreEngine/AssetManagement/AssetExporter.h"

#include "Editor/Common/TextureIconManager.h"

#include "Utilities/Files/FileWatcher.h"
#include "CoreEngine/Scenes/SceneManager.h"

#include "InputEngine/InputMapper.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#include "Game/Game.h"
#include "InputEngine/Input.h"

#include "AssetEngine/AssetImporter/AssetImporter.h"
#include "AssetEngine/AssetPipeline.h"
#include "AssetEngine/PathManager.h"

#include "Editor/EditorProjectManager.h"

namespace Eclipse::Editor
{
	ErrorCode EditorContext::Init()
	{
		DebugLogger::OverwriteDefaultCoutBuffer();

		//PlatformIntegration::Discord::SetupWithID(1425504148681658383);
		//PlatformIntegration::Discord::SetLargeImage("eclipsemoonnobg");

		EditorProjectManager pm;

		PathManager::Init(pm.LoadOrSelectProject());

		PathManager::OnProjectSet += IconManager::LoadIconsFile;

		//InitPaths(); // Init default paths
		Engine::Init(); // Init the game engine




		myWindow = Utilities::MainSingleton::GetInstance<GLFWwindow*>();

		GraphicsEngine::SetWindowIcon((PathManager::GetEngineAssets() / "Icons/EclipseMoonNoBG.png").generic_string().c_str());

		ImGui_Impl::ImplementImGui(myWindow);

		myWindowManager.Begin();

		


		LoadFonts();

		return ErrorCode::SUCCESS;
	}


	void EditorContext::InitPaths()
	{

	}


	bool EditorContext::BeginFrame()
	{
		bool beginRet = Engine::BeginFrame();
		ImGui_Impl::NewFrame();
		return beginRet;
	}


	void EditorContext::Update()
	{
		FileWatcher::InvokeEvents();

		Engine::Update();
		IconManager::Update();

		ImGui::PushFont(fontSmall);

		myWindowManager.Update();

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

		ImGui::PopFont();
	}

	void EditorContext::Render()
	{
		DrawPlayGameButtons();
		ImGui_Impl::Render();
	}

	void EditorContext::EndFrame()
	{
		Engine::EndFrame();
	}

	void EditorContext::End()
	{
		myWindowManager.End();
	}

	void EditorContext::DrawPlayGameButtons()
	{
		int windowSizeX = TemporarySettingsSingleton::Get().GetResolutionX() * 0.5f;
		int windowSizeY = TemporarySettingsSingleton::Get().GetResolutionY() * 0.5f;
		Math::Vector2i windowPosition = GraphicsEngine::GetWindowPosition();

		ImGui::Begin("TestGameButons", (bool*)1, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

		 if (!Game::IsPlaying || Game::IsPaused)
		 {
		 	if (ImGui::Button(ICON_FA_PLAY) || Input::GetKeyDown(Keycode::F5))
		 	{
		 		Game::IsPlaying = true;
		 		Game::IsPaused = false;

		 		SceneLoader::Save(SceneManager::GetActiveScene());

		 		ImGui::End();
		 		return;
		 	}
		 }


		 if (Game::IsPlaying)
		 {
		 	if (!Game::IsPaused)
		 	{
		 		if (ImGui::Button(ICON_FA_PAUSE))
		 			Game::IsPaused = !Game::IsPaused;
		 	}

		 	ImGui::SameLine();
		 	if (ImGui::Button(ICON_FA_STOP))
		 	{
		 		Game::IsPlaying = false;
		 		Game::IsPaused = false;

		 		SceneManager::ReloadActiveScene();
		 	}
		 }

		ImVec2 buttonsWindowSize = ImGui::GetWindowSize();
		ImGui::SetWindowPos(ImVec2(windowPosition.x + windowSizeX - buttonsWindowSize.x * 0.5f, windowPosition.y));

		ImGui::End();
	}



	void EditorContext::LoadFonts()
	{
		ImGuiIO& io = ImGui::GetIO();

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;

		std::string arial = (PathManager::GetEngineAssets() / "Fonts/ARIAL.TTF").generic_string();
		std::string faSolid900 = (PathManager::GetEngineAssets() / "Fonts/FontAwesome/7/fa-solid-900.otf").generic_string();
		std::string faBrands400 = (PathManager::GetEngineAssets() / "Fonts/FontAwesome/7/fa-brands-400.otf").generic_string();
		std::string faRegular400 = (PathManager::GetEngineAssets() / "Fonts/FontAwesome/7/fa-regular-400.otf").generic_string();

		fontTiny = io.Fonts->AddFontFromFileTTF(arial.c_str(), 12.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 12.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 12.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 12.0f, &icons_config, icons_ranges);

		fontSmall = io.Fonts->AddFontFromFileTTF(arial.c_str(), 16.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 16.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 16.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 16.0f, &icons_config, icons_ranges);

		fontMedium = io.Fonts->AddFontFromFileTTF(arial.c_str(), 20.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 20.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 20.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 20.0f, &icons_config, icons_ranges);

		fontLarge = io.Fonts->AddFontFromFileTTF(arial.c_str(), 32.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 32.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 32.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 32.0f, &icons_config, icons_ranges);

		fontExtraLarge = io.Fonts->AddFontFromFileTTF(arial.c_str(), 70.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 70.f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 70.f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 70.f, &icons_config, icons_ranges);

		io.Fonts->Build();

		io.FontDefault = fontSmall;
	}
}
#endif