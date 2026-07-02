#pragma once

#include "CoreEngine/Input/Input.h"
#include <wtypes.h>

namespace Eclipse
{
	struct ComponentEntry final
	{
		const char* name;
		const char* rttiType;
		Eclipse::Component* (__cdecl* createFunc)(unsigned char* address);
		size_t size;
	};

	struct ComponentRegistrySnapshot final
	{
		ComponentEntry* components = nullptr;
		int count = 0;
	};



	typedef ComponentRegistrySnapshot(*RegisterComponentsFunc)();

	HMODULE gameDll;

	class GameLoader
	{
	public:
		static void LoadGameDLL();
		static void UnloadGameDLL();
	};
}