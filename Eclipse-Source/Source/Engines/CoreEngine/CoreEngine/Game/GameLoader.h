#pragma once

namespace Eclipse
{

	struct ComponentEntry final
	{
		const char* name;
		Eclipse::Component* (__cdecl* createFunc)();
	};

	struct ComponentRegistrySnapshot final
	{
		ComponentEntry* components = nullptr;
		int count;
	};

	typedef ComponentRegistrySnapshot (*RegisterComponentsFunc)();

	class GameLoader
	{
	public:
		static void LoadGameDLL();
	};
}