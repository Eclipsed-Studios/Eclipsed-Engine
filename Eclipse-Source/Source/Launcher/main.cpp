#include <iostream>

#include "EclipsedEngine/Editor/EditorApplication.h"
#include <windows.h>

#include <filesystem>

int main()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_SHOW);
    //ShowWindow(console, SW_HIDE);

    auto p = std::filesystem::current_path();

    Eclipse::Editor::EditorApplication editorApplication;

    editorApplication.Init();

    while (editorApplication.Update());

    editorApplication.Shutdown();
}