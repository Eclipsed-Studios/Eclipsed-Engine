
#include "EclipsedEngine/Core/EclipsedEngine.h"
#include "Editor/Editor.h"
#include <iostream>
#include <Windows.h>

#include "ImGui/imgui.h"
#include "EclipsedEngine/Graphics/RendererManager.h"
#include "EclipsedEngine/Graphics/IRenderer.h"

#include "EclipsedEngine/Input/Keycodes.h"

//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Eclipse::Engine engine;
	engine.Init();

	ImGui::SetCurrentContext((ImGuiContext*)engine.GetImGuiContext());

	Eclipse::Editor::Editor editor;
	editor.Init(engine.GetImGuiContext());



	while (!engine.ShouldClose())
	{
		engine.BeginFrame();

		editor.Test();

		engine.Render();
		
		engine.EndFrame();
	}
}