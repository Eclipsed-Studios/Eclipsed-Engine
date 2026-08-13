#pragma once

#include "Input/Input.h"
#include <wtypes.h>
#include "ECS/Component.h"

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
	struct ComponentEntry final
	{
		const char* name;
		const char* rttiType;
		Component* (__cdecl* createFunc)(unsigned char* address);
		size_t size;
	};

	struct ComponentRegistrySnapshot final
	{
		ComponentEntry* components = nullptr;
		int count = 0;
	};



	typedef ComponentRegistrySnapshot(*RegisterComponentsFunc)();

	class ECL_API GameLoader
	{
	public:
		static void LoadGameDLL();
		static void UnloadGameDLL();

	private:
		static HMODULE gameDll;
	};
}