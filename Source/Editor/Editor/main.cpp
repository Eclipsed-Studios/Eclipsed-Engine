#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

#include <chrono>

using namespace ENGINE_NAMESPACE;

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
	Editor::EditorContext editor;
	ErrorCode result = editor.Init();

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