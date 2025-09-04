#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

using namespace ENGINE_NAMESPACE;

int main(int argsCount, char* args[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
	Editor::EditorContext editor;
	ErrorCode result = editor.Init();

	if (result != ErrorCode::SUCCESS)
		return 1;

	while (editor.Begin())
	{
		editor.Update();
		editor.Render();
		editor.End();
	}
}