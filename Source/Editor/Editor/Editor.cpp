#include "Editor.h"

#include "EclipsedEngine/Graphics/IRenderer.h"
#include "EclipsedEngine/Graphics/RendererManager.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	void Editor::Init(void* imguiCtx)
	{
		ImGui::SetCurrentContext((ImGuiContext*)imguiCtx);
	}

	void Editor::BeginFrame()
	{

	}
	
	void Editor::Render()
	{
	}
	
	void Editor::EndFrame()
	{

	}
}