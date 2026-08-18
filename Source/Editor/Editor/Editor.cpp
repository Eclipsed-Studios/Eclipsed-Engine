#include "Editor.h"

#include "Views/ViewManager.h"
#include "Views/AbstractView.h"

#include "ImGui/imgui.h"

#include "Views/Types/AssetBrowserView.h"

namespace Eclipse::Editor
{
	void Editor::Init(void* imguiCtx)
	{
		ImGui::SetCurrentContext((ImGuiContext*)imguiCtx);
		ViewManager::Init();
	}

	void Editor::BeginFrame()
	{

	}
	
	void Editor::Render()
	{
		ViewManager::Update();
	}
	
	void Editor::EndFrame()
	{

	}
}