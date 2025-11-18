#include <iostream>

#include "EclipsedRuntime/Editor/EditorApplication.h"
#include <windows.h>

int main()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_SHOW);
    //ShowWindow(console, SW_HIDE);

    Eclipse::Editor::EditorApplication editorApplication;

    editorApplication.Init();

    while (editorApplication.Update());

    editorApplication.Shutdown();
}