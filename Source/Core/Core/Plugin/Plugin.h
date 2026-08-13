#pragma once

#include <unordered_map>
#include <string>

namespace Eclipse::Core
{
	class IPlugin;

	typedef Eclipse::Core::IPlugin* (*CreatePluginFunc)();
	typedef void (*DestroyPluginFunc)(Eclipse::Core::IPlugin* plugin);

	struct Plugin
	{
	public:
		explicit Plugin(const char* pluginPath);

		Plugin(const Plugin&) = delete;
		Plugin& operator=(const Plugin&) = delete;

		Plugin(Plugin&&) = default;
		Plugin& operator=(Plugin&&) = default;

	public:
		CreatePluginFunc createPlugin;
		DestroyPluginFunc destroyPlugin;
		void* dll;

	public:
		void* GetFunc(const char* procAddress);
	};
}