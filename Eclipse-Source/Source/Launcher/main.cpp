#include "EclipsedEngine/Editor/EditorApplication.h"
#include <windows.h>

#include <filesystem>

int main()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_SHOW); 

    Eclipse::Editor::EditorApplication editorApplication;

    editorApplication.Init();

    while (editorApplication.Update());

    editorApplication.Shutdown();
}