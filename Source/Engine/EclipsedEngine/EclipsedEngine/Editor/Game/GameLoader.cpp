#include "GameLoader.h"

#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include <Windows.h>

void Eclipse::GameLoader::LoadGameDLL()
{
	gameDll = LoadLibraryA((PathManager::GetGameDllBuildPath() / "Game.dll").generic_string().c_str());
	if (!gameDll)
	{
		ComponentRegistry::ClearRegisteredGameComponents();
		return;
	}

	RegisterComponentsFunc registerFunc = (RegisterComponentsFunc)GetProcAddress(gameDll, "RegisterComponents");

	ComponentRegistrySnapshot o = registerFunc();

	ComponentRegistry::ClearRegisteredGameComponents();

	for (int i = 0; i < o.count; i++)
	{
		const auto comp = o.components[i];

		ComponentRegistry::RegisterComponent(
			comp.name,
			comp.rttiType,
			[create = comp.createFunc, size = comp.size](unsigned gameObjId, unsigned compID) -> Component*
			{
				return ComponentManager::Get().AddComponentWithID(gameObjId, compID, create, size);
			},
			[create = comp.createFunc, size = comp.size](unsigned gameObjId) -> Component*
			{
				return ComponentManager::Get().AddComponent(gameObjId, create, size);
			},
			true
		);
	}
}

void Eclipse::GameLoader::UnloadGameDLL()
{
	if (gameDll)
	{
		FreeLibrary(gameDll);
	}
}
