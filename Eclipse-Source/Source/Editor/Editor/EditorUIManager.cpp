#include "EditorUIManager.h"

#include "ImGui/ImGui_Impl.h"
#include "Editor/Common/TextureIconManager.h"

namespace Eclipse::Editor
{
	void EditorUIManager::Init()
	{
		GLFWwindow* window = Utilities::MainSingleton::GetInstance<GLFWwindow*>();
		ImGui_Impl::ImplementImGui(window);

		IconManager::LoadIconsFile();
		LoadFonts();

		myWindowManager.Begin();
	}

	void EditorUIManager::BeginFrame()
	{
		ImGui_Impl::NewFrame();
		ImGui::PushFont(FontSmall);
	}

	void EditorUIManager::Update()
	{
		myWindowManager.Update();
		ImGui::PopFont();
	}
	
	void EditorUIManager::Render()
	{
		ImGui_Impl::Render();
	}

	void EditorUIManager::LoadFonts()
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

		FontTiny = io.Fonts->AddFontFromFileTTF(arial.c_str(), 12.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 12.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 12.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 12.0f, &icons_config, icons_ranges);

		FontSmall = io.Fonts->AddFontFromFileTTF(arial.c_str(), 16.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 16.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 16.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 16.0f, &icons_config, icons_ranges);

		FontMedium = io.Fonts->AddFontFromFileTTF(arial.c_str(), 20.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 20.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 20.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 20.0f, &icons_config, icons_ranges);

		FontLarge = io.Fonts->AddFontFromFileTTF(arial.c_str(), 32.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 32.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 32.0f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 32.0f, &icons_config, icons_ranges);

		FontExtraLarge = io.Fonts->AddFontFromFileTTF(arial.c_str(), 70.0f);
		io.Fonts->AddFontFromFileTTF(faSolid900.c_str(), 70.f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faBrands400.c_str(), 70.f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromFileTTF(faRegular400.c_str(), 70.f, &icons_config, icons_ranges);

		io.Fonts->Build();

		io.FontDefault = FontSmall;
	}
}