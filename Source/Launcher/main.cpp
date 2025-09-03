#include <iostream>

#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#include "TemporarySettingsSingleton.h"

#include <chrono>

#include "Engine.h"
#include "PlatformIntegration/DiscordIntegration.h"

using namespace ENGINE_NAMESPACE;

ErrorCode Init()
{
    PlatformIntegration::Discord::SetupWithID(1401121853829025922);
    PlatformIntegration::Discord::SetLargeImage("noah1");

    Engine::Init();

    return ErrorCode::SUCCESS;
}

int Begin()
{
    Engine::Begin();
    return 1;
}

void Update()
{
    Engine::Update();
}

void End()
{
    Engine::End();
}

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
    ErrorCode result = Init();

    if (result != ErrorCode::SUCCESS)
        return 1;

    while (Begin())
    {
        Update();
        End();
    }
}