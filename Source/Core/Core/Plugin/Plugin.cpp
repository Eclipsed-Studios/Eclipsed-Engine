#include "PluginManager.h"

#include <Windows.h>
#include <iostream>

#include "IPlugin.h"

namespace Eclipse::Core
{
	Plugin::Plugin(const char* pluginPath)
	{
		dll = LoadLibraryA(pluginPath);
		if (!dll)
		{
			std::cout << "PluginManager: Failed to load plugin." << std::endl;
			return;
		}

		createPlugin = (CreatePluginFunc)GetFunc("CreatePlugin");
		destroyPlugin = (DestroyPluginFunc)GetFunc("DestroyPlugin");
	}

	void* Plugin::GetFunc(const char* procAddress)
	{
		return GetProcAddress((HMODULE)dll, procAddress);
	}
}