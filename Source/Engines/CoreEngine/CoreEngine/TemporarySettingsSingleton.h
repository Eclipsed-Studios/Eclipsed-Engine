#include "string"

#include "rapidjson/rapidjson/rapidjson.h"
#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/filereadstream.h"

#include <fstream>

struct GLFWwindow;

namespace ENGINE_NAMESPACE
{
    class TemporarySettingsSingleton
    {
    public:
        enum class WindowSizeType;

        void Init(const std::string &settingsPath)
        {
            FILE *fileP = fopen(settingsPath.c_str(), "rb");
            char readBuffer[2048];
            rapidjson::FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

            rapidjson::Document doc;
            doc.ParseStream(fileReadStream);
            fclose(fileP);

            myGameName = doc["GameName"].GetString();
            myGameTitle = doc["GameTitle"].GetString();

            auto &gameSettings = doc["InGameSettings"];

            float resolutionX = gameSettings["Resolution"]["X"].GetInt();
            float resolutionY = gameSettings["Resolution"]["Y"].GetInt();

            SetResolution(resolutionX, resolutionY);

            myWindowSizeType = static_cast<WindowSizeType>(gameSettings["Fullscreen"].GetInt());
            myNumberOfRenderBuffer = gameSettings["NumberOfRenderBuffer"].GetInt();
        }

        TemporarySettingsSingleton() = default;
        ~TemporarySettingsSingleton() = default;

        static TemporarySettingsSingleton &Get()
        {
            static TemporarySettingsSingleton instance;
            return instance;
        }

        const char *GetGameName() { return myGameName.c_str(); };
        const char *GetGameTitle() { return myGameTitle.c_str(); };

        // Change to vector2i
        int GetResolutionX() { return resX; };
        int GetResolutionY() { return resY; };

        void SetResolution(int anX, int anY)
        {
            resX = anX;
            resY = anY;

            OneDivResolutionX = 1 / resX;
            OneDivResolutionY = 1 / resY;
        }

        WindowSizeType GetWindowSizeType() { return myWindowSizeType; };
        int GetNumRenderBuffers() { return myNumberOfRenderBuffer; };

        GLFWwindow *myWindow;

    private:
        std::string myGameName;
        std::string myGameTitle;

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