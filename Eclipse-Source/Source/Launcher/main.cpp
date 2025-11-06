#include <iostream>

#include "Editor/EditorApplication.h"
#include "Editor/Editor.h"

#include "Utilities/ErrorCodes.h"

#include <windows.h>

#include <chrono>

using namespace Eclipse;

//
//static ErrorCode Init()
//{
//    Editor::EditorContext::Init();
//
//    return ErrorCode::SUCCESS;
//}
//
//static int BeginFrame()
//{
//    return Editor::EditorContext::BeginFrame();
//}
//
//static void Update()
//{
//    Editor::EditorContext::Update();
//    Editor::EditorContext::Render();
//}
//
//static void EndFrame()
//{
//    Editor::EditorContext::EndFrame();
//}
//
//static void End()
//{
//    Editor::EditorContext::End();
//}


int main()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);

    Editor::EditorApplication editorApplication;

    editorApplication.Init();

    while (editorApplication.Update());

    editorApplication.Shutdown();
}