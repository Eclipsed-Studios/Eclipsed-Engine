#pragma once

#include "Config.h"
#include "Presets/BuildPresets.h"
#include "Core/PathManager.h"
#include <unordered_map>
#include <filesystem>

#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Configs
{
	class ECL_API ConfigManager
	{
	public:
		static void Init();
		static Config& GetConfig(const char* name);

		static void LoadOrCreate(Config& conf, const char* configPath);

	private:
		static std::unordered_map<std::string, Config> configs;
	};
}