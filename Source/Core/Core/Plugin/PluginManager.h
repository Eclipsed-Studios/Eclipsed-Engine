#pragma once

#include <unordered_map>
#include <string>

#include "Plugin.h"

namespace Eclipse::Core
{
	class PluginManager final
	{
	public:
		void CompileAndLoadPlugin(const char* pluginPath, const char* pluginSource);
		void ReloadPlugin(const char* pluginPath);
		void LoadPlugin(const char* pluginPath);
		void CompileAndReloadPlugin(const char* pluginPath, const char* pluginSource);

	private:
		bool CompilePlugin(const char* pluginSource);

	private:
		std::unordered_map<std::string, Plugin> loadedPlugins;
	};
}