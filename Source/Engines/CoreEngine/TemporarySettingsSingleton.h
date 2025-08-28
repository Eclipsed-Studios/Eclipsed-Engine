#include "string"

#include "rapidjson/rapidjson/rapidjson.h"
#include "rapidjson/rapidjson/document.h"

#include "fstream"
#include "rapidjson/rapidjson/filereadstream.h"

struct GLFWwindow;

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

        auto& gameSettings = doc["InGameSettings"];

        resX = gameSettings["Resolution"]["X"].GetInt();
        resY = gameSettings["Resolution"]["Y"].GetInt();

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
    int GetResultionX() { return resX; };
    int GetResultionY() { return resY; };

    void SetResolution(int anX, int anY)
    {
        resX = anX;
        resY = anY;
    }

    WindowSizeType GetWindowSizeType() { return myWindowSizeType; };
    int GetNumRenderBuffers() { return myNumberOfRenderBuffer; };
    
    GLFWwindow* myWindow;

private:
    std::string myGameName;
    std::string myGameTitle;

    // Change to vector2i
    int resX;
    int resY;

    enum class WindowSizeType
    {
        WINDOWED = 0,
        WINDOWEDFULLSCEEN = 1,
        FULLSCREEN = 2
    } myWindowSizeType;

    int myNumberOfRenderBuffer;
};