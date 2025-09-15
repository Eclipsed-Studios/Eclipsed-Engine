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
        int windowSizeX = TemporarySettingsSingleton::Get().GetResolutionX() * 0.5f;
        int windowSizeY = TemporarySettingsSingleton::Get().GetResolutionY() * 0.5f;
        Math::Vector2i windowPosition = GraphicsEngine::GetWindowPosition();

        ImGui::Begin("TestGameButons", (bool*)1, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Play"))
        {
            if (Engine::game.myIsPlaying)
            {
                Engine::game.myIsPaused = false;
                Engine::game.myIsPlaying = false;

                if (!firstSceneOnPlay.empty())
                    SceneLoader::Load(firstSceneOnPlay.c_str());
            }
            else
            {
                Engine::game.myIsPaused = false;
                Engine::game.myIsPlaying = true;

                if (!firstSceneOnPlay.empty())
                {
                    firstSceneOnPlay = SceneLoader::GetActiveScene();
                    SceneLoader::Save(firstSceneOnPlay.c_str());
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
            Engine::game.myIsPaused = !Engine::game.myIsPaused;
        ImGui::SameLine();
        ImGui::Button("Stop");

        ImVec2 buttonsWindowSize = ImGui::GetWindowSize();
        ImGui::SetWindowPos(ImVec2(windowPosition.x + windowSizeX - buttonsWindowSize.x * 0.5f, windowPosition.y));

        ImGui::End();


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