#include <iostream>

#include "Editor/EditorApplication.h"
#include <windows.h>

using namespace Eclipse;

int main()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_SHOW);
    //ShowWindow(console, SW_HIDE);

    Editor::EditorApplication editorApplication;

    editorApplication.Init();

    while (editorApplication.Update());

    editorApplication.Shutdown();
}