#include "GameLoader.h"

#include "EntityEngine/ComponentManager.h"


void Eclipse::GameLoader::LoadGameDLL()
{
	gameDll = LoadLibraryA((PathManager::GetProjectRoot() / "Cache/Debug/Game.dll").generic_string().c_str());
	if (!gameDll) return;

	RegisterComponentsFunc registerFunc = (RegisterComponentsFunc)GetProcAddress(gameDll, "RegisterComponents");
	InitGameFunction initGame = (InitGameFunction)GetProcAddress(gameDll, "InitGame");

	initGame(&Utilities::MainSingleton::GetInstance<Input>(),
		&Utilities::MainSingleton::GetInstance<Time>());

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

void Eclipse::GameLoader::UnloadGameDLL()
{
	if (gameDll)
	{
		FreeLibrary(gameDll);
	}
}
