#include "EclipsedEngine.h"

#include "EclipsedEngine/Graphics/RendererManager.h"
#include "EclipsedEngine/Graphics/IRenderer.h"
#include "MainSingleton.h"
#include "ImGui/imgui.h"
#include "ImGui/External/implot.h"
#include "EclipsedEngine/Core/PathManager.h"
#include "EclipsedEngine/Core/Timer.h"
#include "EclipsedEngine/Assets/AssetManager.h"
#include "EclipsedEngine/Assets/AssetImporter.h"
#include "EclipsedEngine/Plugin/PluginManager.h"
#include "EclipsedEngine/Components/Transform2D.h"

namespace Eclipse
{
	void Engine::Init()
	{
		PathManager::Init();
		PathManager::SetProjectPath("C:/Users/zulto/Desktop/MyFiles/Projects/Project-Nova");

		ComponentManager::Init();
		Assets::AssetManager::Init();
		Timer::Init();

		renderer = &Graphics::RendererManager::LoadRenderer(Graphics::RendererAPI::OpenGL);
		MainSingleton::AddInstance(renderer);

		renderer->Init();

		input = renderer->CreateInput();
		input->Init();

		//PluginManager::Compile("C:/Users/zulto/Desktop/GamePlugin");

		GameObject* gameobject = ComponentManager::CreateGameObject();

		gameobject->AddComponent<Transform2D>();
		gameobject->AddComponent<SpriteRenderer2D>();

		ImGui_Init();
	}

	void Engine::LateInit()
	{
		Assets::AssetImporter::ImportAssets(PathManager::GetAssetsPath(), "Assets");
	}



	bool Engine::ShouldClose()
	{
		return renderer->ShouldWindowClose();
	}

	void* Engine::GetImGuiContext()
	{
		return ImGui::GetCurrentContext();
	}

	void Engine::EndFrame()
	{
		renderer->EndFrame();
	}

	void Engine::BeginFrame()
	{
		Timer::Update();

		renderer->BeginFrame();
		input->Update();

		ImGui_NewFrame();
	}

	void Engine::Render()
	{
		renderer->Render();

		ImGui_Render();
	}



	void Engine::ImGui_Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();


		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigWindowsMoveFromTitleBarOnly = true;
		io.IniFilename = nullptr;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// Corners
			style.WindowRounding = 4.0f;
			style.ChildRounding = 4.0f;
			style.FrameRounding = 3.0f;
			style.PopupRounding = 3.0f;
			style.ScrollbarRounding = 3.0f;
			style.GrabRounding = 3.0f;
			style.TabRounding = 3.0f;

			// Eclipse Theme (Yellow Base + Orange Highlights + Black Background)
			ImVec4* colors = ImGui::GetStyle().Colors;

			colors[ImGuiCol_Text] = ImVec4(1.00f, 0.95f, 0.70f, 1.00f); // Golden yellow
			colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.45f, 0.25f, 1.00f);

			colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Deep eclipse black
			colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.08f, 0.05f, 0.95f);

			colors[ImGuiCol_Border] = ImVec4(1.00f, 0.70f, 0.20f, 0.40f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

			colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.12f, 0.08f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.60f, 0.20f, 0.60f); // Soft orange glow
			colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.70f, 0.25f, 0.80f); // Yellow-orange

			colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.07f, 0.05f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.95f, 0.60f, 0.20f, 1.00f); // Eclipse rim orange
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

			colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.85f, 0.70f, 0.20f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.95f, 0.60f, 0.25f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.75f, 0.30f, 1.00f);

			colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.85f, 0.35f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.80f, 0.25f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.70f, 0.30f, 1.00f);

			colors[ImGuiCol_Button] = ImVec4(0.20f, 0.18f, 0.12f, 1.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.95f, 0.60f, 0.20f, 0.85f); // Orange hover
			colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.75f, 0.30f, 1.00f); // Warm yellow active

			colors[ImGuiCol_Header] = ImVec4(0.20f, 0.18f, 0.12f, 0.55f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.95f, 0.60f, 0.20f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.75f, 0.30f, 1.00f);

			colors[ImGuiCol_Separator] = ImVec4(0.95f, 0.75f, 0.30f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.95f, 0.60f, 0.20f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.75f, 0.30f, 1.00f);

			colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.75f, 0.30f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.95f, 0.60f, 0.20f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.75f, 0.35f, 0.95f);

			colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.10f, 0.08f, 1.00f);  // Neutral dark
			colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.78f, 0.30f, 0.95f);  // Brighter yellow highlight
			colors[ImGuiCol_TabActive] = ImVec4(0.80f, 0.50f, 0.15f, 1.00f);  // Amber/orange active
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.07f, 0.07f, 0.97f);  // Faded background tab
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.15f, 0.12f, 1.00f);  // Slightly brighter but still muted

			colors[ImGuiCol_DockingPreview] = ImVec4(0.95f, 0.65f, 0.25f, 0.70f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

			colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.85f, 0.40f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.95f, 0.55f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.80f, 0.30f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95f, 0.55f, 0.20f, 1.00f);

			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.95f, 0.60f, 0.20f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.85f, 0.30f, 0.90f);

			colors[ImGuiCol_NavHighlight] = ImVec4(0.95f, 0.65f, 0.25f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.85f, 0.50f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.95f, 0.65f, 0.25f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.95f, 0.65f, 0.25f, 0.35f);

		}

		//io.FontDefault = io.Fonts->AddFontFromFileTTF((PathManager::GetEngineAssetsPath() / "Fonts/ARIAL.TTF").generic_string().c_str(), 16);

		Graphics::IRenderer& r = Graphics::RendererManager::GetRenderer();
		r.ImGui_Init(ImGui::GetCurrentContext());

		ImPlot::CreateContext();
	}

	void Engine::ImGui_NewFrame()
	{
		Graphics::IRenderer& r = Graphics::RendererManager::GetRenderer();
		r.ImGui_NewFrame();
		ImGui::NewFrame();
	}

	void Engine::ImGui_Render()
	{
		Graphics::IRenderer& r = Graphics::RendererManager::GetRenderer();
		ImGui::Render();
		r.ImGui_Render();
	}
}