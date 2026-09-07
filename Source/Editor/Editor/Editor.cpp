#include "Editor.h"

#include "Views/ViewManager.h"
#include "Views/EditorViewRegistry.h"

#include "ImGui/imgui.h"

//#include "Views/Types/AssetBrowserView.h"

#include "MainMenuBar.h"
#include "ProjectManager.h"

#include "EclipsedEngine/Assets/AssetImporter.h"
#include "EclipsedEngine/Core/PathManager.h"
#include "EditorLayout.h"

namespace Eclipse::Editor
{
	void Editor::Init(void* imguiCtx)
	{
		ImGui::SetCurrentContext((ImGuiContext*)imguiCtx);
		//ViewManager::Init();
		ProjectManager::LoadOrSelectProject();

		Assets::AssetImporter::ImportAssets(PathManager::GetEngineAssetsPath(), "Engine Assets");

		EditorLayout::Init();
	}

	void Editor::Shutdown()
	{
		EditorLayout::Shutdown();
	}

	void Editor::BeginFrame()
	{

	}
	
	void Editor::Render()
	{
		MainMenuBar::Draw();
		EditorLayout::Draw();
		//ViewManager::Update();
	}
	
	void Editor::EndFrame()
	{
		EditorLayout::EndFrame();
	}
}