#include "Editor.h"

#include "MainSingleton.h"

#include "Engine.h"
#include "ImGui/ImGui_Impl.h"
#include "PlatformIntegration/DiscordIntegration.h"

#include "SettingsManager.h"

#include "Files/MetaFileRegistry.h"

#include "defines.h"

#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include <fstream>
#include <rapidjson/rapidjson/stringbuffer.h>
#include <rapidjson/rapidjson/prettywriter.h>

#include "Scenes/SceneLoader.h"
#include <iostream>

namespace Eclipse::Editor
{
    ErrorCode EditorContext::Init()
    {
        DebugLogger::OverwriteDefaultCoutBuffer();
        MetaFileRegistry::Load();

        PlatformIntegration::Discord::SetupWithID(1401121853829025922);
        PlatformIntegration::Discord::SetLargeImage("noah1");

        Engine::Init();

        myWindow = Utilities::MainSingleton::GetInstance<GLFWwindow*>();

        ImGui_Impl::ImplementImGui(myWindow);

        myWindowManager.Begin();

        return ErrorCode::SUCCESS;
    }

    bool EditorContext::BeginFrame()
    {
        bool beginRet = Engine::BeginFrame();
        ImGui_Impl::NewFrame();
        return beginRet;
    }
    

    void EditorContext::Update()
    {
        Engine::Update();
        myWindowManager.Update();

        if (Input::GetKeyDown(Keycode::F1))
        {
            SceneLoader::Save(ASSET_PATH"Scenes/TestScene.json");
        }
        else  if (Input::GetKeyDown(Keycode::F2))
        {
            SceneLoader::Load(ASSET_PATH"Scenes/TestScene.json");
        }
    }

    void EditorContext::Render()
    {
        ImGui_Impl::Render();
    }

    void EditorContext::EndFrame()
    {
        Engine::EndFrame();
    }

    void EditorContext::End()
    {
        MetaFileRegistry::Save();
        myWindowManager.End();
        SettingsManager::Save();
    }
}