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

#include "Font-Awesome-6/IconsFontAwesome6.h"

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

        LoadFonts();

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

        ImGui::PushFont(fontSmall);

        myWindowManager.Update();

        if (Input::GetKeyDown(Keycode::F1))
        {
            SceneLoader::Save(ASSET_PATH"Scenes/TestScene.json");
        }
        else  if (Input::GetKeyDown(Keycode::F2))
        {
            SceneLoader::Load(ASSET_PATH"Scenes/TestScene.json");
        }

        ImGui::PopFont();

        if (Input::GetKeyDown(Keycode::DELETE_KEY))
        {
            GameObject currentObject = HierarchyWindow::CurrentGameObjectID;

            ComponentManager::Destroy(currentObject);
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

    void EditorContext::LoadFonts()
    {
        ImGuiIO& io = ImGui::GetIO();

        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;

        fontTiny = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/ARIAL.TTF", 12.0f);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-solid-900.TTF", 12.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-brands-400.TTF", 12.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-regular-400.TTF", 12.0f, &icons_config, icons_ranges);
        
        fontSmall = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/ARIAL.TTF", 16.0f);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-solid-900.TTF", 16.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-brands-400.TTF", 16.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-regular-400.TTF", 16.0f, &icons_config, icons_ranges);

        fontMedium = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/ARIAL.TTF", 20.0f);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-solid-900.TTF", 20.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-brands-400.TTF", 20.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-regular-400.TTF", 20.0f, &icons_config, icons_ranges);

        fontLarge = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/ARIAL.TTF", 32.0f);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-solid-900.TTF", 32.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-brands-400.TTF", 32.0f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-regular-400.TTF", 32.0f, &icons_config, icons_ranges);

        fontExtraLarge = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/ARIAL.TTF", 70.0f);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-solid-900.TTF", 70.f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-brands-400.TTF", 70.f, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH"Fonts/FontAwesome/fa-regular-400.TTF", 70.f, &icons_config, icons_ranges);

        io.Fonts->Build();

        io.FontDefault = fontSmall;
    }
}