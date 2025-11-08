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

    for (int i = 0; i < o.count; i++)
    {
        const auto comp = o.components[i];

        ComponentRegistry::Register(
            comp.name,
            [create = comp.createFunc, size = comp.size](unsigned gameObjId, unsigned compID) -> Component*
            {
                return ComponentManager::AddComponentWithID(gameObjId, compID, create, size);
            }
        );

        ComponentRegistry::RegisterInspector(
            comp.name,
            [create = comp.createFunc, size = comp.size](unsigned gameObjId) -> Component*
            {
                return ComponentManager::AddComponent(gameObjId, create, size);
            }
        );
    }
}
