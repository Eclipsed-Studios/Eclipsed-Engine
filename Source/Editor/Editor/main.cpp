#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

#include "IconsFontAwesome6.h"
#include "FontAwesomeRegular.h"

using namespace Eclipse;

int main(int argsCount, char* args[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
	ErrorCode result = Editor::EditorContext::Init();

	if (result != ErrorCode::SUCCESS)
		return 1;

	while (Editor::EditorContext::BeginFrame())
	{
		Editor::EditorContext::Update();
		Editor::EditorContext::Render();
		Editor::EditorContext::EndFrame();
	}

	Editor::EditorContext::End();
}