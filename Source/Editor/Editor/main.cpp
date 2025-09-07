#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

#include "IconsFontAwesome6.h"
#include "FontAwesomeRegular.h"

using namespace ENGINE_NAMESPACE;

int main(int argsCount, char* args[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
	Editor::EditorContext editor;
	ErrorCode result = editor.Init();

	ImGuiIO& io = ImGui::GetIO();
	io.FontDefault = io.Fonts->AddFontFromFileTTF(ASSET_PATH "Quicksand-VariableFont_wght.ttf", 18);

	// ImFontConfig fontAwesomeConfig;
	// fontAwesomeConfig.MergeMode = true;
	// fontAwesomeConfig.PixelSnapH = true;
	// constexpr float fontAwesomeSize = 16.0f;
	// fontAwesomeConfig.GlyphMinAdvanceX = fontAwesomeSize;
	// static constexpr ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	// TemporarySettingsSingleton::Get().iconFont = io.Fonts->AddFontFromMemoryCompressedBase85TTF(FontAwesomeRegular_compressed_data_base85, 18, &fontAwesomeConfig, iconRanges);

	if (result != ErrorCode::SUCCESS)
		return 1;

	while (editor.BeginFrame())
	{
		editor.Update();
		editor.Render();
		editor.EndFrame();
	}

	editor.End();
}