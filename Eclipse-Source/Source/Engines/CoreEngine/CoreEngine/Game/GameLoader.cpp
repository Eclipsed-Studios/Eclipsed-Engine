#include "GameLoader.h"

void Eclipse::GameLoader::LoadGameDLL()
{
    HMODULE hModule = LoadLibrary("F:/Projects/Eclipse-Game-Engine/Eclipse-Source/Game/Debug/Game.dll");
    if (!hModule) {
        return;
    }

    RegisterComponentsFunc registerFunc =
        (RegisterComponentsFunc)GetProcAddress(hModule, "RegisterComponents");

    ComponentRegistrySnapshot o = registerFunc();



    Eclipse::Component* comp = o.components[0].createFunc();
}
