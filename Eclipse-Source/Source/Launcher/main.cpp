#include <iostream>

#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

#include <chrono>

using namespace Eclipse;

#ifdef _EDITOR

#include "Editor/Editor.h"

static ErrorCode Init()
{
    Editor::EditorContext::Init();

    return ErrorCode::SUCCESS;
}

static int BeginFrame()
{
    return Editor::EditorContext::BeginFrame();
}

static void Update()
{
    Editor::EditorContext::Update();
    Editor::EditorContext::Render();
}

static void EndFrame()
{
    Editor::EditorContext::EndFrame();
}

static void End()
{
    Editor::EditorContext::End();
}

#elif _GAME

#include "Engine.h"

static ErrorCode Init()
{
    Engine::Init();

    return ErrorCode::SUCCESS;
}

static int BeginFrame()
{
    return Engine::BeginFrame();
}

static void Update()
{
    Engine::Update();
}

static void EndFrame()
{
    Engine::EndFrame();
}

static void End()
{
    // End the engine.
}

#endif

int main(int argsCount, char* args[])
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);

    ErrorCode result = Init();

    if (result != ErrorCode::SUCCESS)
        return 1;

    while (BeginFrame())
    {
        Update();
        EndFrame();
    }

    End();
}