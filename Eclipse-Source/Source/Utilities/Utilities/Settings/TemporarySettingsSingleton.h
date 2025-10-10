#pragma once

#include "string"

#include "rapidjson/rapidjson/rapidjson.h"
#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/filereadstream.h"

#include <fstream>

#include "stb_image/stb_image.h"

//#include "ImGui/ImGui/imgui.h"

namespace Eclipse
{
    class TemporarySettingsSingleton
    {
    public:
        enum class WindowSizeType;

        void Init(const std::string& settingsPath)
        {
            FILE* fileP = fopen(settingsPath.c_str(), "rb");
            char readBuffer[2048];
            rapidjson::FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

            rapidjson::Document doc;
            doc.ParseStream(fileReadStream);
            fclose(fileP);

            myGameName = doc["GameName"].GetString();
            myGameTitle = doc["GameTitle"].GetString();

            auto& gameSettings = doc["InGameSettings"];

            float resolutionX = gameSettings["Resolution"]["X"].GetInt();
            float resolutionY = gameSettings["Resolution"]["Y"].GetInt();

            SetResolution(resolutionX, resolutionY);

            myWindowSizeType = static_cast<WindowSizeType>(gameSettings["Fullscreen"].GetInt());
            myNumberOfRenderBuffer = gameSettings["NumberOfRenderBuffer"].GetInt();
        }

        TemporarySettingsSingleton() = default;
        ~TemporarySettingsSingleton() = default;

        static TemporarySettingsSingleton& Get()
        {
            static TemporarySettingsSingleton instance;
            return instance;
        }

        void SetWindowTitle(const char* aWindowTitle);

        const char* GetGameName() { return myGameName.c_str(); };
        const char* GetGameTitle() { return myGameTitle.c_str(); };

        // Change to vector2i
        int GetResolutionX() { return resX; };
        int GetResolutionY() { return resY; };

        float GetOneDivResolutionX() { return OneDivResolutionX; };
        float GetOneDivResolutionY() { return OneDivResolutionY; };

        float GetResolutionRatio() { return resolutionRatio; }

        void SetResolution(int anX, int anY)
        {
            resX = anX;
            resY = anY;

            OneDivResolutionX = 1.f / static_cast<float>(resX);
            OneDivResolutionY = 1.f / static_cast<float>(resY);

            resolutionRatio = static_cast<float>(resY) / static_cast<float>(resX);
        }

        WindowSizeType GetWindowSizeType() { return myWindowSizeType; };
        int GetNumRenderBuffers() { return myNumberOfRenderBuffer; };

        // public:
        //     ImFont* iconFont;

        float resolutionRatioGameView = 1;
    private:
        std::string myGameName;

        std::string myGameTitle;
        std::string myCreatedGameTitle;

        float resolutionRatio = 1;

        // Change to vector2i
        int resX;
        int resY;

        float OneDivResolutionX;
        float OneDivResolutionY;

        enum class WindowSizeType
        {
            WINDOWED = 0,
            WINDOWEDFULLSCEEN = 1,
            FULLSCREEN = 2
        } myWindowSizeType;

        int myNumberOfRenderBuffer;
    };
}