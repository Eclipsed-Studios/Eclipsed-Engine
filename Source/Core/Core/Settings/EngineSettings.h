#pragma once

#include "SettingsBase.hpp"

namespace Eclipse::Settings
{
	struct EngineSettings : public BaseSettings<EngineSettings>
	{
		static constexpr const char* EngineName = "Trust Me";
		static constexpr const char* GetEngineName()
		{
			return EngineName;
		}

		static constexpr const char* EngineVersion = "1.0.0";
		static constexpr const char* GetEngineVersion()
		{
			return EngineVersion;
		}




		SETTINGS_DATA{
			int test = 0;

			SERIALIZE(MAKE_NVP(test))
		};

		BASE_SETTINGS(EngineSettings, "engine");
	};
}