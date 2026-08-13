#include "PluginManager.h"

#include <Windows.h>
#include <iostream>

#include "IPlugin.h"

namespace Eclipse::Core
{
	void PluginManager::LoadPlugin(const char* pluginPath)
	{
		std::string path = std::string(pluginPath);
		auto [it, inserted] = loadedPlugins.emplace(path, Plugin(pluginPath));

		if (!inserted) {
			std::cout << "PluginManager: Failed to load plugin." << std::endl;
		}
	}

	void PluginManager::CompileAndReloadPlugin(const char* pluginPath, const char* pluginSource)
	{
		const bool compilingSucceded = CompilePlugin(pluginSource);
	}

	bool PluginManager::CompilePlugin(const char* pluginSource)
	{
		// Compile the plugin
		// return true if succeded

		return false;
	}

	void PluginManager::CompileAndLoadPlugin(const char* pluginPath, const char* pluginSource)
	{
		const bool compilingSucceded = CompilePlugin(pluginSource);
		if (!compilingSucceded)
		{
			// Compiling failed 
			return;
		}

		LoadPlugin(pluginPath);
	}

	void PluginManager::ReloadPlugin(const char* pluginPath)
	{

	}
}