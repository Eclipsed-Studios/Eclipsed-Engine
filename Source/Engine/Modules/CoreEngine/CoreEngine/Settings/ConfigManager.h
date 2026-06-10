#pragma once

#include "Config.h"
#include "Presets/BuildPresets.h"
#include "CoreEngine/PathManager.h"
#include <unordered_map>
#include <filesystem>


namespace Eclipse::Configs
{
	class ConfigManager
	{
	public:
		static void Init();
		static Config& GetConfig(const char* name);

		static void LoadOrCreate(Config& conf, const char* configPath);

	private:
		static std::unordered_map<std::string, Config> configs;
	};
}